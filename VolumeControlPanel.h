/*
==============================================================================

VolumeControlPanel.h
Created: 23 Jun 2019 4:46:53pm
Author:  Administrator

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class VolumeControlPanel : public Component
{
public:
	VolumeControlPanel(CapstoneSynthAudioProcessor& p);
	~VolumeControlPanel();

	void paint(Graphics&) override;
	void resized() override;

private:
	Slider gainSlider;
	Slider harmonicVolumeDropoff;
	Label gainSliderLabel;
	Label harmonicVolumeDropoffLabel;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> harmonicVolumeDropoffAttachment;

	CapstoneSynthAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VolumeControlPanel)
};
