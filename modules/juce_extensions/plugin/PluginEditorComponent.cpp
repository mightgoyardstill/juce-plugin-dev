#include "PluginEditorComponent.h"

//==============================================================================
namespace plugin
{

PluginEditorComponent::PluginEditorComponent (std::unique_ptr<juce::AudioProcessorEditor> editorIn, 
                                              std::function<juce::Grid(juce::Component*)> layoutIn = nullptr)
    : editor (std::move (editorIn)), layout (std::move (layoutIn))
{
    addAndMakeVisible (editor.get());
    childBoundsChanged (editor.get());
}

void PluginEditorComponent::childBoundsChanged (juce::Component* child)
{
    if (child != editor.get()) 
        return;
    
    else if (child == editor.get())
    {
        auto size = editor.get()->getBounds();

        if (!layout) 
        {
            setSize(size.getWidth(), size.getHeight());
            return;
        }

        else if (layout)
        {
            auto grid = layout(editor.get());

            for (const auto& item : grid.items)
                if (item.associatedComponent != editor.get())
                    if (auto comp = item.associatedComponent; !comp->isVisible()) 
                            addAndMakeVisible(comp);

            auto [w, h] = calculateGridComponentSizes(grid);

            setSize((w + size.getWidth()), (h + size.getHeight()));
            grid.performLayout(getBounds());
        }
    }
}

void PluginEditorComponent::setScaleFactor (float scale)
{
    if (editor != nullptr) 
        editor->setScaleFactor (scale);
}

void PluginEditorComponent::setLayout (std::function<juce::Grid(juce::Component*)> func)
{
    layout = std::move (func);
    childBoundsChanged (editor.get());
}

float PluginEditorComponent::getTotalAbsoluteSize (const juce::Array<juce::Grid::TrackInfo>& tracks, 
                                                   juce::Grid::Px gapSize) noexcept
{
    float totalCellSize = 0.0f;

    for (const auto& trackInfo : tracks)
        if (! trackInfo.isFractional() || trackInfo.isAuto())
            totalCellSize += trackInfo.getSize();

    float totalGap = tracks.size() > 1 ? static_cast<float> ((tracks.size() - 1) * gapSize.pixels)
                                        : 0.0f;
    return totalCellSize + totalGap;
}

std::pair<int, int> PluginEditorComponent::calculateGridComponentSizes(const juce::Grid& grid)
{
    return { getTotalAbsoluteSize(grid.templateColumns, grid.columnGap), 
                getTotalAbsoluteSize(grid.templateRows, grid.rowGap) };
}

} // namespace plugin