#include "PluginParameters.h"

namespace brickstortion::params
{
juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(distortionOn, "Distortion On", true));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(goofyMode, "Goofy Mode", false));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        drive,
        "Brick Drive",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        0.35f,
        "",
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) { return juce::String(juce::jmap(value, 1.0f, 30.0f), 1) + "x"; },
        [](const juce::String& text) { return juce::jlimit(0.0f, 1.0f, (text.getFloatValue() - 1.0f) / 29.0f); }));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        tone,
        "Tone",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        0.5f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        mix,
        "Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        1.0f,
        "%",
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) { return juce::String(value * 100.0f, 0) + "%"; },
        [](const juce::String& text) { return text.getFloatValue() * 0.01f; }));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        output,
        "Output",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f),
        0.0f,
        "dB"));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        character,
        "Character",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        0.5f));

    return { parameters.begin(), parameters.end() };
}
}
