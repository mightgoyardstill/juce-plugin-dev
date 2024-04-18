#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace plugin
{
    //==============================================================================
    class AudioProcessor  : public juce::AudioProcessor
    {
    public:
        //==============================================================================
        AudioProcessor();
        explicit AudioProcessor(const BusesProperties&);
        ~AudioProcessor() override;

        //==============================================================================
        void prepareToPlay (double, int) override;
        void releaseResources() override;
        using juce::AudioProcessor::processBlock;

        bool isBusesLayoutSupported (const BusesLayout&) const override;
        static juce::AudioProcessor::BusesProperties getDefaultBusProperties();

        //==============================================================================
        const juce::String getName() const override;
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        bool isMidiEffect() const override;
        double getTailLengthSeconds() const override;

        //==============================================================================
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int) override;
        
        //==============================================================================
        const juce::String getProgramName (int) override;
        void changeProgramName (int, const juce::String&) override;

        //==============================================================================
        void getStateInformation (juce::MemoryBlock&) override;
        void setStateInformation (const void*, int) override;

        //==============================================================================
        bool hasEditor() const override;
    };

} // namespace pluginextensions