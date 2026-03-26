#pragma once

#include <JuceHeader.h>
#include "Theme.h"

namespace brickstortion::ui
{
class BrickSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    explicit BrickSliderLookAndFeel(Theme& themeRef) : theme(themeRef) {}

    void drawLinearSlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          float,
                          float,
                          const juce::Slider::SliderStyle,
                          juce::Slider&) override;

private:
    Theme& theme;
};

class BrickSlider : public juce::Slider
{
public:
    explicit BrickSlider(Theme& theme);
    ~BrickSlider() override;

private:
    BrickSliderLookAndFeel lookAndFeel;
};
}
