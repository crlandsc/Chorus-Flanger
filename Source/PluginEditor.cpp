/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChorusFlangerAudioProcessorEditor::ChorusFlangerAudioProcessorEditor (ChorusFlangerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(510, 440);

    auto& params = processor.getParameters();


    // Dry/Wet Slider ------------------------------------------------------------------------------------------
    AudioParameterFloat* dryWetParameter = (AudioParameterFloat*)params.getUnchecked(0);

    // Slider Attributes
    addAndMakeVisible(mDryWetSlider); // make visible on UI
    mDryWetSlider.setLookAndFeel(&sliderLookAndFeel); // set look and feel
    mDryWetSlider.setBounds(20, 70, 150, 150);
    mDryWetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    //mDryWetSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 75, 25); // Can add a value text box to slider
    mDryWetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDryWetSlider.setRange(dryWetParameter->range.start, dryWetParameter->range.end);
    mDryWetSlider.setValue(*dryWetParameter);

    // Slider Listeners
    mDryWetSlider.onValueChange = [this, dryWetParameter] {*dryWetParameter = mDryWetSlider.getValue(); };
    mDryWetSlider.onDragStart = [dryWetParameter] {dryWetParameter->beginChangeGesture(); };
    mDryWetSlider.onDragEnd = [dryWetParameter] {dryWetParameter->endChangeGesture(); };

    // Label Attributes
    addAndMakeVisible(mDryWetLabel); // make visible on UI
    mDryWetLabel.setLookAndFeel(&labelLookAndFeel); // set look and feel
    mDryWetLabel.setText("Dry/Wet", juce::dontSendNotification); // define text to go in label
    mDryWetLabel.attachToComponent(&mDryWetSlider, false); // 'false' locates label above slider
    mDryWetLabel.setFont(juce::Font(16.0f, juce::Font::bold)); // define font style
    mDryWetLabel.setJustificationType(juce::Justification::centred); // justification within label area


    // Depth Slider ------------------------------------------------------------------------------------------
    AudioParameterFloat* depthParameter = (AudioParameterFloat*)params.getUnchecked(1);

    // Slider Attributes
    addAndMakeVisible(mDepthSlider);
    mDepthSlider.setLookAndFeel(&sliderLookAndFeel); // set look and feel
    mDepthSlider.setBounds(170, 70, 150, 150);
    mDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mDepthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mDepthSlider.setRange(depthParameter->range.start, depthParameter->range.end);
    mDepthSlider.setValue(*depthParameter);

    // Slider Listeners
    mDepthSlider.onValueChange = [this, depthParameter] {*depthParameter = mDepthSlider.getValue(); };
    mDepthSlider.onDragStart = [depthParameter] {depthParameter->beginChangeGesture(); };
    mDepthSlider.onDragEnd = [depthParameter] {depthParameter->endChangeGesture(); };

    // Label Attributes
    addAndMakeVisible(mDepthLabel); // make visible on UI
    mDepthLabel.setLookAndFeel(&labelLookAndFeel); // set look and feel
    mDepthLabel.setText("Depth", juce::dontSendNotification); // define text to go in label
    mDepthLabel.attachToComponent(&mDepthSlider, false); // 'false' locates label above slider
    mDepthLabel.setFont(juce::Font(16.0f, juce::Font::bold)); // define font style
    mDepthLabel.setJustificationType(juce::Justification::centred); // justification within label area


    // Rate Slider ------------------------------------------------------------------------------------------
    AudioParameterFloat* rateParameter = (AudioParameterFloat*)params.getUnchecked(2);

    // Slider Attributes
    addAndMakeVisible(mRateSlider);
    mRateSlider.setLookAndFeel(&sliderLookAndFeel); // set look and feel
    mRateSlider.setBounds(320, 70, 150, 150);
    mRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mRateSlider.setRange(rateParameter->range.start, rateParameter->range.end);
    mRateSlider.setValue(*rateParameter);

    // Slider Listeners
    mRateSlider.onValueChange = [this, rateParameter] {*rateParameter = mRateSlider.getValue(); };
    mRateSlider.onDragStart = [rateParameter] {rateParameter->beginChangeGesture(); };
    mRateSlider.onDragEnd = [rateParameter] {rateParameter->endChangeGesture(); };

    // Label Attributes
    addAndMakeVisible(mRateLabel); // make visible on UI
    mRateLabel.setLookAndFeel(&labelLookAndFeel); // set look and feel
    mRateLabel.setText("Rate", juce::dontSendNotification); // define text to go in label
    mRateLabel.attachToComponent(&mRateSlider, false); // 'false' locates label above slider
    mRateLabel.setFont(juce::Font(16.0f, juce::Font::bold)); // define font style
    mRateLabel.setJustificationType(juce::Justification::centred); // justification within label area


    // Phase Offset Slider ----------------------------------------------------------------------------------
    AudioParameterFloat* phaseParameter = (AudioParameterFloat*)params.getUnchecked(3);

    // Slider Attributes
    addAndMakeVisible(mPhaseOffsetSlider);
    mPhaseOffsetSlider.setLookAndFeel(&sliderLookAndFeel); // set look and feel
    mPhaseOffsetSlider.setBounds(20, 270, 150, 150);
    mPhaseOffsetSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mPhaseOffsetSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mPhaseOffsetSlider.setRange(phaseParameter->range.start, phaseParameter->range.end);
    mPhaseOffsetSlider.setValue(*phaseParameter);

    // Slider Listeners
    mPhaseOffsetSlider.onValueChange = [this, phaseParameter] {*phaseParameter = mPhaseOffsetSlider.getValue(); };
    mPhaseOffsetSlider.onDragStart = [phaseParameter] {phaseParameter->beginChangeGesture(); };
    mPhaseOffsetSlider.onDragEnd = [phaseParameter] {phaseParameter->endChangeGesture(); };

    // Label Attributes
    addAndMakeVisible(mPhaseOffsetLabel); // make visible on UI
    mPhaseOffsetLabel.setLookAndFeel(&labelLookAndFeel); // set look and feel
    mPhaseOffsetLabel.setText("Phase Offset", juce::dontSendNotification); // define text to go in label
    mPhaseOffsetLabel.attachToComponent(&mPhaseOffsetSlider, false); // 'false' locates label above slider
    mPhaseOffsetLabel.setFont(juce::Font(16.0f, juce::Font::bold)); // define font style
    mPhaseOffsetLabel.setJustificationType(juce::Justification::centred); // justification within label area


    // Feeback Slider ---------------------------------------------------------------------------------------
    AudioParameterFloat* feedbackParameter = (AudioParameterFloat*)params.getUnchecked(4);

    // Slider Attributes
    addAndMakeVisible(mFeedbackSlider);
    mFeedbackSlider.setLookAndFeel(&sliderLookAndFeel); // set look and feel
    mFeedbackSlider.setBounds(170, 270, 150, 150);
    mFeedbackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mFeedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mFeedbackSlider.setRange(feedbackParameter->range.start, feedbackParameter->range.end);
    mFeedbackSlider.setValue(*feedbackParameter);

    // Slider Listeners
    mFeedbackSlider.onValueChange = [this, feedbackParameter] {*feedbackParameter = mFeedbackSlider.getValue(); };
    mFeedbackSlider.onDragStart = [feedbackParameter] {feedbackParameter->beginChangeGesture(); };
    mFeedbackSlider.onDragEnd = [feedbackParameter] {feedbackParameter->endChangeGesture(); };

    // Label Attributes
    addAndMakeVisible(mFeedbackLabel); // make visible on UI
    mFeedbackLabel.setLookAndFeel(&labelLookAndFeel); // set look and feel
    mFeedbackLabel.setText("Feedback", juce::dontSendNotification); // define text to go in label
    mFeedbackLabel.attachToComponent(&mFeedbackSlider, false); // 'false' locates label above slider
    mFeedbackLabel.setFont(juce::Font(16.0f, juce::Font::bold)); // define font style
    mFeedbackLabel.setJustificationType(juce::Justification::centred); // justification within label area


    // ComboBox Type ----------------------------------------------------------------------------------------
    AudioParameterInt* typeParameter = (AudioParameterInt*)params.getUnchecked(5);

    mType.setBounds(340, 320, 100, 30);
    mType.addItem("Chorus", 1);
    mType.addItem("Flanger", 2);
    addAndMakeVisible(mType);

    mType.onChange = [this, typeParameter] {
        typeParameter->beginChangeGesture();
        *typeParameter = mType.getSelectedItemIndex();
        typeParameter->endChangeGesture();
    };

    mType.setSelectedItemIndex(*typeParameter);
}

ChorusFlangerAudioProcessorEditor::~ChorusFlangerAudioProcessorEditor()
{
}

//==============================================================================
void ChorusFlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::lightskyblue);
    g.setFont(juce::Font(24.0f, juce::Font::bold));
    g.drawFittedText ("Chorus/Flanger", getLocalBounds(), juce::Justification::centredTop, 1);
}

void ChorusFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    /*
    const int border = 20;
    const int dialWidth = getWidth() / 4 - border;
    const int dialHeight = getHeight() - border - 100;

    mDryWetSlider.setBounds(border+200, border, dialWidth, dialHeight);
    */
}
