#include "BrickSlider.h"

namespace brickstortion::ui
{
void BrickSliderLookAndFeel::drawLinearSlider(juce::Graphics& g,
                                              int x,
                                              int y,
                                              int width,
                                              int height,
                                              float sliderPos,
                                              float,
                                              float,
                                              const juce::Slider::SliderStyle,
                                              juce::Slider&)
{
    auto bounds = juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height));

    g.setColour(theme.panel.brighter(0.12f));
    g.fillRoundedRectangle(bounds, 10.0f);

    auto track = bounds.reduced(16.0f, bounds.getHeight() * 0.33f);
    g.setColour(theme.background.brighter(0.3f));
    g.fillRoundedRectangle(track, 8.0f);

    const auto clampedPos = juce::jlimit(track.getX(), track.getRight(), sliderPos);
    juce::Rectangle<float> brick(clampedPos - 34.0f, bounds.getCentreY() - 26.0f, 68.0f, 52.0f);

    juce::Path front;
    front.addRoundedRectangle(brick, 6.0f);
    g.setColour(theme.accent);
    g.fillPath(front);

    juce::Path top;
    top.startNewSubPath(brick.getX(), brick.getY());
    top.lineTo(brick.getX() + 14.0f, brick.getY() - 10.0f);
    top.lineTo(brick.getRight() + 14.0f, brick.getY() - 10.0f);
    top.lineTo(brick.getRight(), brick.getY());
    top.closeSubPath();
    g.setColour(theme.accentBright);
    g.fillPath(top);

    juce::Path side;
    side.startNewSubPath(brick.getRight(), brick.getY());
    side.lineTo(brick.getRight() + 14.0f, brick.getY() - 10.0f);
    side.lineTo(brick.getRight() + 14.0f, brick.getBottom() - 10.0f);
    side.lineTo(brick.getRight(), brick.getBottom());
    side.closeSubPath();
    g.setColour(theme.accent.darker(0.22f));
    g.fillPath(side);

    g.setColour(theme.text.withAlpha(0.4f));
    for (int row = 0; row < 2; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            const auto px = brick.getX() + 9.0f + col * 18.0f + (row % 2 == 1 ? 8.0f : 0.0f);
            const auto py = brick.getY() + 8.0f + row * 16.0f;
            g.drawRoundedRectangle({ px, py, 14.0f, 12.0f }, 2.0f, 1.0f);
        }
    }
}

BrickSlider::BrickSlider(Theme& theme)
    : juce::Slider(juce::Slider::LinearHorizontal, juce::Slider::NoTextBox),
      lookAndFeel(theme)
{
    setLookAndFeel(&lookAndFeel);
}

BrickSlider::~BrickSlider()
{
    setLookAndFeel(nullptr);
}
}
