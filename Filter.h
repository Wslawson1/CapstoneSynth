/*
  ==============================================================================

    Filter.h
    Created: 10 Jun 2019 6:52:29pm
    Author:  Administrator

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(CapstoneSynthAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	Slider filterCutoffSlider;
	Slider filterResonanceSlider;
	ComboBox filterTypeMenu;

	Label filterCutoffLabel;
	Label filterResonanceLabel;
	Label filterTypeLabel;
	
	CapstoneSynthAudioProcessor& processor;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeFilterCutoff;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeResonance;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
