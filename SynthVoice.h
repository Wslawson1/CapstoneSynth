/*
  ==============================================================================

	SynthVoice.h
	Created: 17 May 2019 9:24:00pm
	Author:  Wesley Slawson

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode//JuceHeader.h"
#include "SynthSound.h"
#include <string>
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:

	bool canPlaySound(SynthesiserSound* sound)
	{
		//Tries to cast sound to a synthsound. If successful, return true
		//if not, returns false and will not play the sound
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	void getOscParams(float* oscType, float* numHarmonics, float* harmonicFactor, float* harmonicOffset)
	{
		this->oscType = (int)*oscType;
		this->numHarmonics = (int)*numHarmonics;
		this->harmonicFactor = (float)*harmonicFactor;
		this->harmonicOffset = (float)*harmonicOffset;
	}

	void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
	{
		env1.setAttack(double(*attack));
		env1.setDecay(double(*decay));
		env1.setSustain(double(*sustain));
		env1.setRelease(double(*release));
	}

	void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
	{
		this->filterType = (int)*filterType;
		this->filterCutoff = *filterCutoff;
		this->filterRes = *filterRes;
	}

	double setHarmonics()
	{
		double theWave = setOscType(0, frequency);
		double theFreq = frequency;
		for (int currentHarmonic = 1; currentHarmonic <= numHarmonics; currentHarmonic++)
		{
			theFreq = theFreq * harmonicFactor + harmonicOffset;
			theWave += setOscType(currentHarmonic, theFreq) / (currentHarmonic + 1);
		}
		return theWave;
	}	
	
	double setOscType(int oscNum, double frequency)
	{
		if (oscType == 0)
			return oscillators[oscNum]->sinewave(frequency);
		if (oscType == 1)
			return oscillators[oscNum]->saw(frequency);
		if (oscType == 2)
			return oscillators[oscNum]->triangle(frequency);
		return oscillators[oscNum]->sinewave(frequency);
	}

	double setEnvelope()
	{
		return env1.adsr(setHarmonics(), env1.trigger) * level;
	}

	double setFilter()
	{
		if (filterType == 0)
			return filter1.lores(setEnvelope(), filterCutoff, filterRes);
		if (filterType == 1)
			return filter1.hires(setEnvelope(), filterCutoff, filterRes);
		if (filterType == 2)
			return filter1.bandpass(setEnvelope(), filterCutoff, filterRes);
		return filter1.lores(setEnvelope(), filterCutoff, filterRes);
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
	{
		env1.trigger = 1;
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}

	void stopNote(float velocity, bool allowTailOff)
	{
		env1.trigger = 0;
		allowTailOff = true;

		if (velocity = 0)
		{
			clearCurrentNote();
		}
	}

	void pitchWheelMoved(int newPitchWheel)
	{
	}

	void controllerMoved(int controllerNumber, int newControllerValue)
	{
	}

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
	{
		for (int sample = 0; sample < numSamples; ++sample)
		{
			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{
				outputBuffer.addSample(channel, startSample, setFilter());
			}
			++startSample;
		}
	}

private:
	double level;
	double frequency;

	maxiOsc* oscillators[6] = { new maxiOsc(), new maxiOsc, new maxiOsc, new maxiOsc, new maxiOsc, new maxiOsc };
	int oscType;
	int numHarmonics;
	float harmonicFactor;
	float harmonicOffset;

	maxiEnv env1;

	maxiFilter filter1;
	int filterType;
	float filterCutoff;
	float filterRes;

};

