/*
  ==============================================================================

    EnvelopePanel.h
    Created: 3 Jun 2019 4:42:49pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class EnvelopePanel    : public Component
{
public:
    EnvelopePanel(SynthFramworkAudioProcessor&);
    ~EnvelopePanel();

    void paint (Graphics&) override;
    void resized() override;

private:

	SynthFramworkAudioProcessor& processor;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel;

	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeAttack;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeDecay;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeSustain;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeRelease;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopePanel)
};
