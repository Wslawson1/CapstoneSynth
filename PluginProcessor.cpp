/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFramworkAudioProcessor::SynthFramworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree (*this, nullptr)
#endif
{
	NormalisableRange<float> attackRange(0.1f, 5000.0f);
	NormalisableRange<float> decayRange(0.1f, 5000.0f);
	NormalisableRange<float> sustainRange(0.01f, 1.0f);
	NormalisableRange<float> releaseRange(0.1f, 5000.0f);
	NormalisableRange<float> numHarmonicsRange(0, 6);
	NormalisableRange<float> harmonicFactorRange(1.01f, 4.0f);
	NormalisableRange<float> harmonicOffsetRange(0.0f, 100.0f);
	NormalisableRange<float> filterCutoffRange(20.0f, 10000.0f);
	NormalisableRange<float> resonanceRange(1.0f, 5.0f);
	NormalisableRange<float> filterTypeRange(0, 2);
	NormalisableRange<float> oscTypeRange(0, 2);

	tree.createAndAddParameter("osctype", "OscType", "OscType", oscTypeRange, 0 ,nullptr, nullptr);
	tree.createAndAddParameter("filtertype", "FilterType", "FilterType", filterTypeRange, 0, nullptr, nullptr);
	tree.createAndAddParameter("filtercutoff", "FilterCutoff", "FilterCutoff", filterCutoffRange, 400.0f, nullptr, nullptr);
	tree.createAndAddParameter("resonance", "Resonance", "Resonance", resonanceRange, 1.0f, nullptr, nullptr);
	tree.createAndAddParameter("attack", "Attack", "Attack", attackRange, 0.1f, nullptr, nullptr);
	tree.createAndAddParameter("decay", "Decay", "Decay", decayRange, 0.1f, nullptr, nullptr);
	tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainRange, 0.5f, nullptr, nullptr);
	tree.createAndAddParameter("release", "Release", "Release", releaseRange, 0.1f, nullptr, nullptr);
	tree.createAndAddParameter("numharmonics", "NumHarmonics", "numHarmonics", numHarmonicsRange, 4, nullptr, nullptr);
	tree.createAndAddParameter("harmonicfactor", "HarmonicFactor", "HarmonicFactor", harmonicFactorRange, 1.01, nullptr, nullptr);
	tree.createAndAddParameter("harmonicoffset", "HarmonicOffset", "HarmonicOffset", harmonicOffsetRange, 5, nullptr, nullptr);

	tree.state = ValueTree("valueTree");

	//Ensures samples from last keypress are no longer present on new instantiation
	//of synth ( or from new keypress ? I think not but maybe )
	mySynth.clearVoices();

	//for five voice synth
	for (int i = 0; i < 5; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}

	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

SynthFramworkAudioProcessor::~SynthFramworkAudioProcessor()
{
}

//==============================================================================
const String SynthFramworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFramworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFramworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFramworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFramworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFramworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFramworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFramworkAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthFramworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFramworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthFramworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

}

void SynthFramworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFramworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthFramworkAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	/*
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	*/

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
	/*
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	*/

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

	/*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
	*/

	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
		{
			myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
										tree.getRawParameterValue("decay"),
										tree.getRawParameterValue("sustain"),
										tree.getRawParameterValue("release"));

			myVoice->getFilterParams(tree.getRawParameterValue("filtertype"),
									  tree.getRawParameterValue("filtercutoff"),
									  tree.getRawParameterValue("resonance"));

			myVoice->getOscParams(tree.getRawParameterValue("osctype"),
				                   tree.getRawParameterValue("numharmonics"),
				                   tree.getRawParameterValue("harmonicfactor"),
				                   tree.getRawParameterValue("harmonicoffset"));
		}
	}
	buffer.clear();
	mySynth.renderNextBlock( buffer, midiMessages, 0, buffer.getNumSamples() );
}

//==============================================================================
bool SynthFramworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthFramworkAudioProcessor::createEditor()
{
    return new SynthFramworkAudioProcessorEditor (*this);
}

//==============================================================================
void SynthFramworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFramworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFramworkAudioProcessor();
}
