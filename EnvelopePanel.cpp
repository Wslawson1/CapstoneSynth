/*
  ==============================================================================

    EnvelopePanel.cpp
    Created: 3 Jun 2019 4:42:49pm
    Author:  Administrator

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopePanel.h"

//==============================================================================
EnvelopePanel::EnvelopePanel(SynthFramworkAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(400, 400);

	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.1f, 5000.0f);
	attackSlider.setValue(0.1f);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	attackSlider.setNumDecimalPlacesToDisplay(1);
	attackSlider.setTextValueSuffix("ms");
	addAndMakeVisible(&attackSlider);

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(0.1f, 5000.0f);
	decaySlider.setValue(0.1f);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	decaySlider.setNumDecimalPlacesToDisplay(1);
	decaySlider.setTextValueSuffix("ms");
	addAndMakeVisible(&decaySlider);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.01f, 1.0f);
	sustainSlider.setValue(0.5f);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	sustainSlider.setNumDecimalPlacesToDisplay(2);
	sustainSlider.setTextValueSuffix("%db");
	addAndMakeVisible(&sustainSlider);

	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f, 5000.0f);
	releaseSlider.setValue(0.1f);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	releaseSlider.setNumDecimalPlacesToDisplay(1);
	releaseSlider.setTextValueSuffix("ms");
	addAndMakeVisible(&releaseSlider);

	addAndMakeVisible(&attackLabel);
	addAndMakeVisible(&decayLabel);
	addAndMakeVisible(&sustainLabel);
	addAndMakeVisible(&releaseLabel);

	attackLabel.setText("A", dontSendNotification);
	decayLabel.setText("D", dontSendNotification);
	sustainLabel.setText("S", dontSendNotification);
	releaseLabel.setText("R", dontSendNotification);

	attackLabel.attachToComponent(&attackSlider, false);
	decayLabel.attachToComponent(&decaySlider, false);
	sustainLabel.attachToComponent(&sustainSlider, false);
	releaseLabel.attachToComponent(&releaseSlider, false);

	sliderTreeAttack = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
	sliderTreeDecay = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
	sliderTreeSustain = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
	sliderTreeRelease = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

EnvelopePanel::~EnvelopePanel()
{
}

void EnvelopePanel::paint (Graphics& g)
{
}

void EnvelopePanel::resized()
{
	int reductionAmt = getLocalBounds().getWidth() / 16;
	juce::Rectangle<int> area = getLocalBounds().reduced(reductionAmt);
	
	int sliderWidth = area.getWidth() / 4;
	attackSlider.setBounds(area.removeFromLeft(sliderWidth));
	decaySlider.setBounds(area.removeFromLeft(sliderWidth));
	sustainSlider.setBounds(area.removeFromLeft(sliderWidth));
	releaseSlider.setBounds(area.removeFromLeft(sliderWidth));
}