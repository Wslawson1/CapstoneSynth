/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================


//using Parameter = AudioProcessorValueTreeState::Parameter;

CapstoneSynthAudioProcessor::CapstoneSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	attackTime(0.1f),
	//tree(*this, nullptr)
	tree(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
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



CapstoneSynthAudioProcessor::~CapstoneSynthAudioProcessor()
{
}

//==============================================================================
const String CapstoneSynthAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool CapstoneSynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool CapstoneSynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool CapstoneSynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double CapstoneSynthAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int CapstoneSynthAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int CapstoneSynthAudioProcessor::getCurrentProgram()
{
	return 0;
}

void CapstoneSynthAudioProcessor::setCurrentProgram(int index)
{
}

const String CapstoneSynthAudioProcessor::getProgramName(int index)
{
	return {};
}

void CapstoneSynthAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void CapstoneSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..

	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

}

void CapstoneSynthAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CapstoneSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void CapstoneSynthAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
			myVoice->getGainParams(tree.getRawParameterValue("gain"), tree.getRawParameterValue("harmonicdropoff"));
		}
	}
	buffer.clear();
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool CapstoneSynthAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CapstoneSynthAudioProcessor::createEditor()
{
	return new CapstoneSynthAudioProcessorEditor(*this);
}

//==============================================================================
void CapstoneSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.

	auto treeState = tree.copyState();
	std::unique_ptr<XmlElement> xml(treeState.createXml());
	copyXmlToBinary(*xml, destData);
}

void CapstoneSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
	{
		if (xmlState->hasTagName(tree.state.getType()))
		{
			tree.replaceState(ValueTree::fromXml(*xmlState));
		}
	}
}

AudioProcessorValueTreeState::ParameterLayout CapstoneSynthAudioProcessor::createParameterLayout()
{
	std::vector < std::unique_ptr<RangedAudioParameter>> params;
	params.push_back(std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5000.0f), 0.1f));
	params.push_back(std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.1f, 5000.0f), 5.0f));
	params.push_back(std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.00f, 1.0f), 0.5f));
	params.push_back(std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5000.0f), 0.1f));

	params.push_back(std::make_unique<AudioParameterInt>("osctype", "OscType", 0, 2, 0));
	params.push_back(std::make_unique<AudioParameterInt>("numharmonics", "numHarmonics", 0, 9, 4));

	params.push_back(std::make_unique<AudioParameterFloat>("harmonicfactor", "HarmonicFactor", NormalisableRange<float>(1.001f, 2.5f), 1.01f));
	params.push_back(std::make_unique<AudioParameterFloat>("harmonicoffset", "HarmonicOffset", NormalisableRange<float>(-100.0f, 100.0f), 0.0f));

	params.push_back(std::make_unique<AudioParameterInt>("filtertype", "FilterType", 0, 2, 0));
	params.push_back(std::make_unique<AudioParameterFloat>("filtercutoff", "FilterCutoff", NormalisableRange<float>(20.0f, 10000.0f), 400.0f));
	params.push_back(std::make_unique<AudioParameterFloat>("resonance", "Resonance", NormalisableRange<float>(1.0f, 5.0f), 1.0f));

	params.push_back(std::make_unique<AudioParameterFloat>("gain", "Gain", NormalisableRange<float>(0.0f, 1.0f), 0.7f));
	params.push_back(std::make_unique<AudioParameterFloat>("harmonicdropoff", "HarmonicDropoff", NormalisableRange<float>(0.0f, 1.0f), 0.7f));

	return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new CapstoneSynthAudioProcessor();
}