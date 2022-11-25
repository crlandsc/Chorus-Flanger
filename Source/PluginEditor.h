/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class SliderLookAndFeel : public LookAndFeel_V4
{
public:
    SliderLookAndFeel()
    {
        setColour(Slider::rotarySliderOutlineColourId, Colours::lightskyblue);
        setColour(Slider::rotarySliderFillColourId, Colours::darkblue);
        setColour(Slider::thumbColourId, Colours::whitesmoke);
    }
};


class LabelLookAndFeel : public LookAndFeel_V4
{
public:
    LabelLookAndFeel()
    {
        setColour(juce::Label::textColourId, juce::Colours::lightskyblue);
    }
};


class ChorusFlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ChorusFlangerAudioProcessorEditor (ChorusFlangerAudioProcessor&);
    ~ChorusFlangerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChorusFlangerAudioProcessor& audioProcessor;

    Slider mDryWetSlider;
    Label mDryWetLabel;

    Slider mDepthSlider;
    Label mDepthLabel;

    Slider mRateSlider;
    Label mRateLabel;

    Slider mPhaseOffsetSlider;
    Label mPhaseOffsetLabel;

    Slider mFeedbackSlider;
    Label mFeedbackLabel;

    ComboBox mType;

    SliderLookAndFeel sliderLookAndFeel;
    LabelLookAndFeel labelLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusFlangerAudioProcessorEditor)
};
