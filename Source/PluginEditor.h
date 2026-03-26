#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/BrickSlider.h"
#include "UI/Theme.h"

namespace brickstortion
{
class AudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioProcessorEditor(AudioProcessor& processor);
    ~AudioProcessorEditor() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    AudioProcessor& processor;
    ui::Theme theme;

    juce::ToggleButton distortionButton { "DISTORTION" };
    juce::ToggleButton goofyButton { "GOOFY" };
    ui::BrickSlider driveSlider;
    juce::Slider toneSlider;
    juce::Slider mixSlider;
    juce::Slider outputSlider;
    juce::Slider characterSlider;

    juce::Label title;
    juce::Label driveLabel;

    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<ButtonAttachment> distortionAttachment;
    std::unique_ptr<ButtonAttachment> goofyAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> toneAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;
    std::unique_ptr<SliderAttachment> outputAttachment;
    std::unique_ptr<SliderAttachment> characterAttachment;

    void configureButton(juce::ToggleButton& button);
    void configureSmallSlider(juce::Slider& slider, const juce::String& suffix);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorEditor)
};
}
