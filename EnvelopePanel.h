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
    EnvelopePanel(CapstoneSynthAudioProcessor&);
    ~EnvelopePanel();

    void paint (Graphics&) override;
    void resized() override;

private:

	CapstoneSynthAudioProcessor& processor;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	Label attackLabel;
	Label decayLabel;
	Label sustainLabel;
	Label releaseLabel;

	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeAttack;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeDecay;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeSustain;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeRelease;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopePanel)
};
