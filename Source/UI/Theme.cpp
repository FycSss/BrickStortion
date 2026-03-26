#include "Theme.h"

namespace brickstortion::ui
{
Theme::Theme()
    : background(juce::Colour::fromRGB(18, 21, 29)),
      panel(juce::Colour::fromRGB(26, 30, 40)),
      accent(juce::Colour::fromRGB(194, 98, 43)),
      accentBright(juce::Colour::fromRGB(242, 140, 67)),
      text(juce::Colours::whitesmoke)
{
}

void Theme::setAssetDirectory(const juce::File& directory)
{
    assetDirectory = directory;
}

juce::Image Theme::getAsset(const juce::String& fileName) const
{
    if (assetDirectory == juce::File{} || !assetDirectory.isDirectory())
        return {};

    const auto file = assetDirectory.getChildFile(fileName);
    return file.existsAsFile() ? juce::ImageFileFormat::loadFrom(file) : juce::Image{};
}
}
