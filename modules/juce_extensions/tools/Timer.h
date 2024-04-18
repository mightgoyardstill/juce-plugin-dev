#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace tools
{
    //==============================================================================
    class Timer : public juce::Timer
    {
    public:
        Timer() = default;
        Timer (std::function<void()> fn);
        ~Timer() override;

        Timer& setCallback (std::function<void()> fn);
    private:
        void timerCallback() override;
        std::function<void()> callbackFn;
    };
}