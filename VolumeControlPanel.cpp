/*
==============================================================================

VolumeControlPanel.cpp
Created: 23 Jun 2019 4:46:53pm
Author:  Administrator

==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "VolumeControlPanel.h"

//==============================================================================
VolumeControlPanel::VolumeControlPanel(CapstoneSynthAudioProcessor& p) :
	processor(p)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	setSize(400, 400);
	gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50.0, 30.0);
	gainSlider.setDoubleClickReturnValue(true, 0.7f);

	harmonicVolumeDropoff.setSliderStyle(Slider::SliderStyle::LinearVertical);
	harmonicVolumeDropoff.setTextBoxStyle(Slider::TextBoxBelow, true, 50.0, 30.0);
	harmonicVolumeDropoff.setDoubleClickReturnValue(true, 0.7);

	addAndMakeVisible(&gainSlider);
	addAndMakeVisible(&harmonicVolumeDropoff);

	gainSliderLabel.setText("gain", dontSendNotification);
	gainSliderLabel.attachToComponent(&gainSlider, false);

	harmonicVolumeDropoffLabel.setText("harmonic gain Dropoff", dontSendNotification);
	harmonicVolumeDropoffLabel.attachToComponent(&harmonicVolumeDropoff, false);

	addAndMakeVisible(&gainSliderLabel);
	addAndMakeVisible(&harmonicVolumeDropoffLabel);

	gainSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "gain", gainSlider);
	harmonicVolumeDropoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "harmonicdropoff", harmonicVolumeDropoff);

}

VolumeControlPanel::~VolumeControlPanel()
{
}

void VolumeControlPanel::paint(Graphics& g)
{
}

void VolumeControlPanel::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

	juce::Rectangle<int> panelBounds = getLocalBounds();

	gainSlider.setBounds(panelBounds.removeFromRight(panelBounds.getWidth() / 2));
	harmonicVolumeDropoff.setBounds(panelBounds);
}
