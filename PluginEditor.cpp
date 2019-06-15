/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFramworkAudioProcessorEditor::SynthFramworkAudioProcessorEditor(SynthFramworkAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), oscGui(p), envelopeGui(p), filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);

	addAndMakeVisible(&oscGui);
	addAndMakeVisible(&envelopeGui);
	addAndMakeVisible(&filterGui);

}

SynthFramworkAudioProcessorEditor::~SynthFramworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFramworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void SynthFramworkAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	int oscAreaReduction = getLocalBounds().getWidth() / 4;
	juce::Rectangle<int> oscArea = getLocalBounds().reduced(oscAreaReduction);
	juce::Rectangle<int> envArea = getLocalBounds().reduced(oscAreaReduction);
	juce::Rectangle<int> filterArea = getLocalBounds().reduced(oscAreaReduction);

	juce::Point<int> oscPosition = getLocalBounds().getPosition();
	//oscPosition.addXY(5, 200);

	oscArea.setPosition(oscPosition);

	juce::Point<int> envPosition = oscPosition;
	envPosition.addXY(oscArea.getWidth(), 0);
	envArea.setPosition(envPosition);

	juce::Point<int> filterPosition = oscPosition;
	filterPosition.addXY(0, oscArea.getHeight());
	filterArea.setPosition(filterPosition);

	oscGui.setBounds(oscArea);	
	envelopeGui.setBounds(envArea);
	filterGui.setBounds(filterArea);
}
