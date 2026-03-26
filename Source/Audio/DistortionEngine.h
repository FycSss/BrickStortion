#pragma once

#include <JuceHeader.h>

namespace brickstortion
{
class DistortionEngine
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void reset();

    void process(juce::AudioBuffer<float>& buffer,
                 bool distortionEnabled,
                 bool goofyEnabled,
                 float driveAmount,
                 float tone,
                 float mix,
                 float outputDb,
                 float character);

private:
    static float processSample(float input, float drive, float character);

    std::array<juce::dsp::IIR::Filter<float>, 2> postToneFilters;
    juce::Random random;
    double sampleRate = 44100.0;
    float goofyPhase = 0.0f;
    int crushCounter = 0;
    float heldSample = 0.0f;
};
}
