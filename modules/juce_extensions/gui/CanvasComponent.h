#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace gui
{
    //==============================================================================
    class CanvasComponent : public juce::Component
    {
    public:
        std::function<void (juce::Graphics&, juce::Component&)> onPaint;
        void paint (juce::Graphics& g) override;
    };
} // namespace gui