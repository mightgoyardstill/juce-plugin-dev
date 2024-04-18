#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

namespace plugin
{
    class ScaledDocumentWindow : public juce::DocumentWindow
    {
    public:
        ScaledDocumentWindow (juce::String, juce::Colour, float);
        float getDesktopScaleFactor() const override;
        void closeButtonPressed() override;
        std::function<void()> onCloseButtonPressed;
    private:
        float desktopScale = 1.0f;
    };

} // namespace plugin