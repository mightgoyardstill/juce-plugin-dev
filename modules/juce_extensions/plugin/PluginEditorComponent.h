#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================

namespace plugin
{
class PluginEditorComponent : public juce::Component
{
public:
    PluginEditorComponent (std::unique_ptr<juce::AudioProcessorEditor>, 
                           std::function<juce::Grid(juce::Component*)>);
    void childBoundsChanged (juce::Component*) override;
    void setScaleFactor (float);
    void setLayout (std::function<juce::Grid(juce::Component*)>);

private:
    std::unique_ptr<juce::AudioProcessorEditor>  editor;
    std::function<juce::Grid(juce::Component*)> layout;

    float getTotalAbsoluteSize (const juce::Array<juce::Grid::TrackInfo>&, juce::Grid::Px) noexcept;
    std::pair<int, int> calculateGridComponentSizes(const juce::Grid&);
};
} // namespace plugin