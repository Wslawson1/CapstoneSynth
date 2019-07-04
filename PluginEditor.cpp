/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CapstoneSynthAudioProcessorEditor::CapstoneSynthAudioProcessorEditor(CapstoneSynthAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), oscGui(p), envelopeGui(p), filterGui(p), gainGui(p)
{
	setSize(600, 600);

	addAndMakeVisible(&oscGui);
	addAndMakeVisible(&envelopeGui);
	addAndMakeVisible(&filterGui);
	addAndMakeVisible(&gainGui);

}

CapstoneSynthAudioProcessorEditor::~CapstoneSynthAudioProcessorEditor()
{
}

//==============================================================================
void CapstoneSynthAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

}

void CapstoneSynthAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	int oscAreaReduction = getLocalBounds().getWidth() / 4;
	juce::Rectangle<int> oscArea = getLocalBounds().reduced(oscAreaReduction);
	juce::Rectangle<int> envArea = getLocalBounds().reduced(oscAreaReduction);
	juce::Rectangle<int> filterArea = getLocalBounds().reduced(oscAreaReduction);
	juce::Rectangle <int > gainArea = getLocalBounds().reduced(oscAreaReduction);

	juce::Point<int> oscPosition = getLocalBounds().getPosition();
	//oscPosition.addXY(5, 200);

	oscArea.setPosition(oscPosition);

	juce::Point<int> envPosition = oscPosition;
	envPosition.addXY(oscArea.getWidth(), 0);
	envArea.setPosition(envPosition);

	juce::Point<int> filterPosition = oscPosition;
	filterPosition.addXY(0, oscArea.getHeight());
	filterArea.setPosition(filterPosition);

	juce::Point<int> gainPosition = filterPosition;
	gainPosition.addXY(filterArea.getWidth(), 0);
	gainArea.setPosition(gainPosition);

	oscGui.setBounds(oscArea);
	envelopeGui.setBounds(envArea);
	filterGui.setBounds(filterArea);
	gainGui.setBounds(gainArea);
}
