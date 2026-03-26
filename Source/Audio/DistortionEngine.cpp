#include "DistortionEngine.h"

namespace brickstortion
{
void DistortionEngine::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    reset();
}

void DistortionEngine::reset()
{
    for (auto& filter : postToneFilters)
    {
        filter.reset();
        filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 5000.0);
    }

    goofyPhase = 0.0f;
    crushCounter = 0;
    heldSample = 0.0f;
}

float DistortionEngine::processSample(float input, float drive, float character)
{
    const auto x = input * drive;
    const auto soft = std::tanh(x);
    const auto hard = juce::jlimit(-1.0f, 1.0f, x);
    return juce::jmap(character, soft, hard);
}

void DistortionEngine::process(juce::AudioBuffer<float>& buffer,
                               bool distortionEnabled,
                               bool goofyEnabled,
                               float driveAmount,
                               float tone,
                               float mix,
                               float outputDb,
                               float character)
{
    if (!distortionEnabled)
        return;

    const auto drive = juce::jmap(driveAmount, 1.0f, 30.0f);
    const auto wet = juce::jlimit(0.0f, 1.0f, mix);
    const auto dry = 1.0f - wet;
    const auto gain = juce::Decibels::decibelsToGain(outputDb);

    const auto cutoff = juce::jmap(tone, 600.0f, 18000.0f);
    for (auto& filter : postToneFilters)
        filter.coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoff);

    const auto numChannels = juce::jmin(buffer.getNumChannels(), 2);
    const auto numSamples = buffer.getNumSamples();

    auto goofyRate = 0.6f + character * 6.4f;
    auto goofyDepth = 0.03f + character * 0.18f;
    const auto bitDepth = juce::jlimit(4, 14, static_cast<int>(14 - driveAmount * 8.0f));
    const auto quantSteps = static_cast<float>((1 << bitDepth) - 1);
    const auto holdSamples = juce::jmax(1, static_cast<int>(sampleRate / juce::jmap(driveAmount, 4200.0f, 1000.0f)));

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* samples = buffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            const auto drySample = samples[i];
            auto wetSample = processSample(drySample, drive, character);

            if (goofyEnabled)
            {
                goofyPhase += goofyRate / static_cast<float>(sampleRate);
                if (goofyPhase > 1.0f)
                    goofyPhase -= 1.0f;

                const auto wobble = 1.0f + std::sin(juce::MathConstants<float>::twoPi * goofyPhase) * goofyDepth;
                wetSample *= wobble;

                if (crushCounter++ % holdSamples == 0)
                {
                    heldSample = wetSample + random.nextFloat() * 0.02f - 0.01f;
                    heldSample = std::round(juce::jlimit(-1.0f, 1.0f, heldSample) * quantSteps) / quantSteps;
                }

                wetSample = 0.55f * wetSample + 0.45f * heldSample;
            }

            wetSample = postToneFilters[static_cast<size_t>(channel)].processSample(wetSample);
            samples[i] = (dry * drySample + wet * wetSample) * gain;
        }
    }
}
}
