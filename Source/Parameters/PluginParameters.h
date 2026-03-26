#pragma once

#include <JuceHeader.h>

namespace brickstortion::params
{
constexpr auto distortionOn = "distortionOn";
constexpr auto goofyMode = "goofyMode";
constexpr auto drive = "drive";
constexpr auto tone = "tone";
constexpr auto mix = "mix";
constexpr auto output = "output";
constexpr auto character = "character";

juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
}
