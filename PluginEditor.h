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

//==============================================================================
/**
*/
class SynthFramworkAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SynthFramworkAudioProcessorEditor (SynthFramworkAudioProcessor&);
    ~SynthFramworkAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    SynthFramworkAudioProcessor& processor;

	Oscillator oscGui;
	EnvelopePanel envelopeGui;
	Filter filterGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthFramworkAudioProcessorEditor)
};
