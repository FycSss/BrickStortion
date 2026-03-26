#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace brickstortion
{
AudioProcessor::AudioProcessor()
    : juce::AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                            .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "PARAMETERS", params::createLayout())
{
}

void AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32>(samplesPerBlock), static_cast<juce::uint32>(getTotalNumOutputChannels()) };
    engine.prepare(spec);
}

void AudioProcessor::releaseResources()
{
    engine.reset();
}

#if ! JucePlugin_IsMidiEffect
bool AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}
#endif

void AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    juce::ignoreUnused(midiMessages);

    for (auto channel = getTotalNumInputChannels(); channel < getTotalNumOutputChannels(); ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());

    const auto distortionEnabled = apvts.getRawParameterValue(params::distortionOn)->load() > 0.5f;
    const auto goofyEnabled = apvts.getRawParameterValue(params::goofyMode)->load() > 0.5f;
    const auto drive = apvts.getRawParameterValue(params::drive)->load();
    const auto tone = apvts.getRawParameterValue(params::tone)->load();
    const auto mix = apvts.getRawParameterValue(params::mix)->load();
    const auto output = apvts.getRawParameterValue(params::output)->load();
    const auto character = apvts.getRawParameterValue(params::character)->load();

    engine.process(buffer, distortionEnabled, goofyEnabled, drive, tone, mix, output, character);
}

void AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary(*xml, destData);
}

void AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        if (xml->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new AudioProcessorEditor(*this);
}
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new brickstortion::AudioProcessor();
}
