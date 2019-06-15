/*
  ==============================================================================

    Oscillator.cpp
    Created: 2 Jun 2019 2:15:32pm
    Author:  Wesley Slawson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFramworkAudioProcessor& p) :
processor(p)
{
	setSize(400, 400);

	oscMenu.addItem("1", 1);
	oscMenu.addItem("2", 2);
	oscMenu.addItem("3", 3);
	oscMenu.addItem("4", 4);
	oscMenu.addItem("5", 5);
	oscMenu.addItem("6", 6);
	addAndMakeVisible(&oscMenu);

	oscSelection.addItem("sine", 1);
	oscSelection.addItem("saw", 2);
	oscSelection.addItem("triangle", 3);
	addAndMakeVisible(&oscSelection);

	oscMenu.setJustificationType(Justification::centred);

	numHarmonicsSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "numharmonics", oscMenu);

	addAndMakeVisible(&oscMenuLabel);
	addAndMakeVisible(&oscSelectionLabel);

	oscMenuLabel.setText("# Harmonics", dontSendNotification);
	oscMenuLabel.attachToComponent(&oscMenu, false);

	oscSelectionLabel.setText("Osc type", dontSendNotification);
	oscSelectionLabel.attachToComponent(&oscSelection, false);

	harmonicFactorSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	harmonicFactorSlider.setRange(0.1f, 5000.0f);
	harmonicFactorSlider.setValue(1.01f);
	harmonicFactorSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	harmonicFactorSlider.setNumDecimalPlacesToDisplay(1);
	addAndMakeVisible(&harmonicFactorSlider);

	harmonicOffsetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	harmonicOffsetSlider.setRange(0.1f, 5000.0f);
	harmonicOffsetSlider.setValue(0.1f);
	harmonicOffsetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50.0, 30.0);
	harmonicOffsetSlider.setNumDecimalPlacesToDisplay(1);
	addAndMakeVisible(&harmonicOffsetSlider);

	addAndMakeVisible(&harmonicFactorLabel);
	addAndMakeVisible(&harmonicOffsetLabel);

	harmonicFactorLabel.setText("harmonic factor", dontSendNotification);
	harmonicOffsetLabel.setText("harmonic offset", dontSendNotification);

	harmonicFactorLabel.attachToComponent(&harmonicFactorSlider, false);
	harmonicOffsetLabel.attachToComponent(&harmonicOffsetSlider, false);

	sliderTreeHarmonicFactor = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "harmonicfactor", harmonicFactorSlider);
	sliderTreeHarmonicOffset = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "harmonicoffset", harmonicOffsetSlider);
	oscTypeSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "osctype", oscSelection);
	harmonicFactorSlider.setSkewFactorFromMidPoint(2.5f);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
}

void Oscillator::resized()
{
	int reductionAmt = getLocalBounds().getWidth() / 16;
	juce::Rectangle<int> area = getLocalBounds().reduced(reductionAmt);

	int oscMenuHeight = area.getHeight() / 4;

	juce::Rectangle<int> oscMenuArea = area.removeFromTop(oscMenuHeight);

	Logger::outputDebugString(std::to_string(area.getHeight()));
	
	int menuWidth = oscMenuArea.getWidth() / 2;

	oscSelection.setBounds(oscMenuArea.removeFromLeft(menuWidth));
	oscMenu.setBounds(oscMenuArea.removeFromLeft(menuWidth));

	int topSpace = area.getHeight() / 5;
	area.removeFromTop(topSpace);

	int sliderWidth = area.getWidth() / 2;
	harmonicFactorSlider.setBounds(area.removeFromLeft(sliderWidth ));
	harmonicOffsetSlider.setBounds(area.removeFromLeft(sliderWidth));
}