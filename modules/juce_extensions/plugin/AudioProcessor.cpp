#include "AudioProcessor.h"

namespace plugin
{
//==============================================================================
AudioProcessor::AudioProcessor() : juce::AudioProcessor (getDefaultBusProperties())
{
}

AudioProcessor::AudioProcessor(const BusesProperties& busProperties) : juce::AudioProcessor (busProperties)
{
}

AudioProcessor::~AudioProcessor()
{
}

//==============================================================================
void AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioProcessor::releaseResources()
{
}

//==============================================================================
bool AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (isMidiEffect())
        return true;
    else
    {
        if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
            && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
                return false;
    }

    #if ! JucePlugin_IsSynth
        if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
            return false;
    #endif
        return true;
}

juce::AudioProcessor::BusesProperties AudioProcessor::getDefaultBusProperties()
{
    return BusesProperties()
    #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        #endif
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
    #endif 
    ;
}

//==============================================================================
const juce::String AudioProcessor::getName() const
{
    return JucePlugin_Name; 
}

bool AudioProcessor::acceptsMidi() const
{
    #if JucePlugin_WantsMidiInput
        return true;
    #else
        return false;
    #endif
}

bool AudioProcessor::producesMidi() const
{
    #if JucePlugin_ProducesMidiOutput
        return true;
    #else
        return false;
    #endif
}

bool AudioProcessor::isMidiEffect() const
{
    #if JucePlugin_IsMidiEffect
        return true;
    #else
        return false;
    #endif
}

double AudioProcessor::getTailLengthSeconds() const
{ 
    return 0.0;
}

//==============================================================================
int AudioProcessor::getNumPrograms()
{ 
    return 1;
}

int AudioProcessor::getCurrentProgram()
{ 
    return 0;
}

void AudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused(index);
}

    
//==============================================================================
const juce::String AudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}


//==============================================================================
void AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused (destData);
}

void AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
bool AudioProcessor::hasEditor() const
{
    return true;
}
    
} // namespace pluginextensions