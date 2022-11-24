/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//#include <include_juce_audio_formats.cpp>
//#include <math.h>
//#include <cmath>
//#  define M_PI (3.1415926536f)
//# define _USE_MATH_DEFINES

# define MAX_DELAY_TIME 2

//==============================================================================
/**
*/
class ChorusFlangerAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    ChorusFlangerAudioProcessor();
    ~ChorusFlangerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    float lin_interp(float sample_x, float sample_x1, float inPhase);

private:

    /* Parameter Declarations */
    AudioParameterFloat* mDryWetParameter; // Controls the mix of dry/wet signal
    AudioParameterFloat* mDepthParameter; // Controls how wide the delay time sweeps
    AudioParameterFloat* mRateParameter; // Controls how quickly delay time sweeps
    AudioParameterFloat* mPhaseOffsetParameter; // Controls the difference between the ReadHead position for the L and R channels
    AudioParameterFloat* mFeedbackParameter; // Controls amount of feedback
    AudioParameterInt* mTypeParameter; // Controls if hte effect will be chorus of flanger

    /* Circular buffer data */
    std::unique_ptr<float[]> mCircularBufferLeft; // smart pointer for circularbuffer to better manage data
    std::unique_ptr<float[]> mCircularBufferRight; // smart pointer for circularbuffer to better manage data

    int mCircularbufferWriteHead;
    int mCircularBufferLength;

    float mFeedbackLeft;
    float mFeedbackRight;

    /* LFO Data */
    float mLFOPhase;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusFlangerAudioProcessor)
};
