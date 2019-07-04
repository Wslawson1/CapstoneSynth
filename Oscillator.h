/*
  ==============================================================================

    Oscillator.h
    Created: 2 Jun 2019 2:15:32pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(CapstoneSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

private:
	ComboBox oscMenu;
	ComboBox oscSelection;
	Slider harmonicFactorSlider;
	Slider harmonicOffsetSlider;

	Label harmonicFactorLabel;
	Label harmonicOffsetLabel;
	Label oscMenuLabel;
	Label oscSelectionLabel;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeSelection;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> numHarmonicsSelection;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeHarmonicFactor;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderTreeHarmonicOffset;

	CapstoneSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
