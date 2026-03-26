#pragma once

#include <JuceHeader.h>

namespace brickstortion::ui
{
class Theme
{
public:
    Theme();

    void setAssetDirectory(const juce::File& directory);
    juce::Image getAsset(const juce::String& fileName) const;

    juce::Colour background;
    juce::Colour panel;
    juce::Colour accent;
    juce::Colour accentBright;
    juce::Colour text;

private:
    juce::File assetDirectory;
};
}
