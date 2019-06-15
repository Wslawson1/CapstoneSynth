/*
  ==============================================================================

    Filter.cpp
    Created: 10 Jun 2019 6:52:29pm
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFramworkAudioProcessor& p) :
	processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(400, 400);

	filterTypeMenu.addItem("lowpass", 1);
	filterTypeMenu.addItem("highpass", 2);
	filterTypeMenu.addItem("bandpass", 3);
	filterTypeMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterTypeMenu);

	filterCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoffSlider.setRange(20.0f, 10000.0f);
	filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	filterCutoffSlider.setNumDecimalPlacesToDisplay(2);
	filterCutoffSlider.setTextValueSuffix("hz");
	sliderTreeFilterCutoff = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filtercutoff", filterCutoffSlider);
	filterCutoffSlider.setSkewFactorFromMidPoint(1000.0);
	addAndMakeVisible(&filterCutoffSlider);

	filterResonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterResonanceSlider.setRange(0.0f, 5.0f);
	filterResonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	filterResonanceSlider.setNumDecimalPlacesToDisplay(2);
	filterResonanceSlider.setTextValueSuffix("db");
	addAndMakeVisible(&filterResonanceSlider);

	filterCutoffLabel.setText("cutoff", dontSendNotification);
	addAndMakeVisible(&filterCutoffLabel);
	filterCutoffLabel.attachToComponent(&filterCutoffSlider, false);

	filterResonanceLabel.setText("reso", dontSendNotification);
	addAndMakeVisible(&filterResonanceLabel);
	filterResonanceLabel.attachToComponent(&filterResonanceSlider, false);

	filterTypeLabel.setText("filterType", dontSendNotification);
	addAndMakeVisible(&filterTypeLabel);
	filterTypeLabel.attachToComponent(&filterTypeMenu, false);

	filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filtertype", filterTypeMenu);
	sliderTreeResonance = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "resonance", filterResonanceSlider);

}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
}

void Filter::resized()
{
	int reductionAmt = getLocalBounds().getWidth() / 16;

	juce::Rectangle<int> area = getLocalBounds().reduced(reductionAmt);

	int menuHeight = area.getHeight() / 4;

	filterTypeMenu.setBounds(area.removeFromTop(menuHeight));

	int labelSpaceHeight = area.getHeight() / 8;
	area.removeFromTop(labelSpaceHeight);

	int sliderWidth = area.getWidth() / 2; 

	filterCutoffSlider.setBounds(area.removeFromLeft(sliderWidth));
	filterResonanceSlider.setBounds(area.removeFromLeft(sliderWidth));

}
