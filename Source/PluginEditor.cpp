#include "PluginEditor.h"

namespace brickstortion
{
AudioProcessorEditor::AudioProcessorEditor(AudioProcessor& p)
    : juce::AudioProcessorEditor(&p),
      processor(p),
      driveSlider(theme)
{
    theme.setAssetDirectory(juce::File(BRICKSTORTION_ASSETS_DIR));

    title.setText("BRICKSTORTION", juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centredLeft);
    title.setColour(juce::Label::textColourId, theme.text);
    title.setFont(juce::FontOptions { 26.0f, juce::Font::bold });
    addAndMakeVisible(title);

    driveLabel.setText("BRICK DRIVE", juce::dontSendNotification);
    driveLabel.setColour(juce::Label::textColourId, theme.text.withAlpha(0.8f));
    driveLabel.setFont(juce::FontOptions { 14.0f, juce::Font::bold });
    addAndMakeVisible(driveLabel);

    configureButton(distortionButton);
    configureButton(goofyButton);

    toneSlider.setName("TONE");
    mixSlider.setName("MIX");
    outputSlider.setName("OUTPUT");
    characterSlider.setName("CHARACTER");
    configureSmallSlider(toneSlider, "");
    configureSmallSlider(mixSlider, "%");
    configureSmallSlider(outputSlider, " dB");
    configureSmallSlider(characterSlider, "");

    addAndMakeVisible(driveSlider);

    auto& paramsState = processor.getParameters();
    distortionAttachment = std::make_unique<ButtonAttachment>(paramsState, params::distortionOn, distortionButton);
    goofyAttachment = std::make_unique<ButtonAttachment>(paramsState, params::goofyMode, goofyButton);
    driveAttachment = std::make_unique<SliderAttachment>(paramsState, params::drive, driveSlider);
    toneAttachment = std::make_unique<SliderAttachment>(paramsState, params::tone, toneSlider);
    mixAttachment = std::make_unique<SliderAttachment>(paramsState, params::mix, mixSlider);
    outputAttachment = std::make_unique<SliderAttachment>(paramsState, params::output, outputSlider);
    characterAttachment = std::make_unique<SliderAttachment>(paramsState, params::character, characterSlider);

    setSize(760, 420);
}

void AudioProcessorEditor::configureButton(juce::ToggleButton& button)
{
    button.setColour(juce::ToggleButton::textColourId, theme.text);
    addAndMakeVisible(button);
}

void AudioProcessorEditor::configureSmallSlider(juce::Slider& slider, const juce::String& suffix)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    slider.setTextValueSuffix(suffix);
    slider.setColour(juce::Slider::rotarySliderFillColourId, theme.accent);
    slider.setColour(juce::Slider::textBoxTextColourId, theme.text);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::textBoxBackgroundColourId, theme.panel.brighter(0.08f));
    slider.setColour(juce::Slider::thumbColourId, theme.accentBright);
    addAndMakeVisible(slider);
}

void AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background);

    auto area = getLocalBounds().reduced(16);

    g.setColour(theme.panel);
    g.fillRoundedRectangle(area.toFloat(), 16.0f);

    g.setColour(theme.accent.withAlpha(0.25f));
    g.fillRoundedRectangle(area.removeFromTop(4).toFloat(), 4.0f);
}

void AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(26);

    auto top = area.removeFromTop(62);
    title.setBounds(top.removeFromLeft(280));

    auto buttons = top.removeFromRight(280);
    distortionButton.setBounds(buttons.removeFromLeft(140).reduced(6));
    goofyButton.setBounds(buttons.removeFromLeft(140).reduced(6));

    driveLabel.setBounds(area.removeFromTop(30));
    driveSlider.setBounds(area.removeFromTop(120));

    area.removeFromTop(12);
    auto bottom = area.removeFromTop(170);
    auto controlWidth = bottom.getWidth() / 4;

    toneSlider.setBounds(bottom.removeFromLeft(controlWidth).reduced(8));
    mixSlider.setBounds(bottom.removeFromLeft(controlWidth).reduced(8));
    outputSlider.setBounds(bottom.removeFromLeft(controlWidth).reduced(8));
    characterSlider.setBounds(bottom.removeFromLeft(controlWidth).reduced(8));
}
}
