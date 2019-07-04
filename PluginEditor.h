/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "EnvelopePanel.h"
#include "Filter.h"
#include "VolumeControlPanel.h"

//==============================================================================
/**
*/
class CapstoneSynthAudioProcessorEditor : public AudioProcessorEditor
{
public:
	CapstoneSynthAudioProcessorEditor(CapstoneSynthAudioProcessor&);
	~CapstoneSynthAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	CapstoneSynthAudioProcessor& processor;

	Oscillator oscGui;
	EnvelopePanel envelopeGui;
	Filter filterGui;
	VolumeControlPanel gainGui;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CapstoneSynthAudioProcessorEditor)
};
