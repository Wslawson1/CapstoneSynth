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
    Oscillator(SynthFramworkAudioProcessor&);
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

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeSelection;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> numHarmonicsSelection;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeHarmonicFactor;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sliderTreeHarmonicOffset;

	SynthFramworkAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
