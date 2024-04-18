#include "CanvasComponent.h"

namespace gui
{
    //==============================================================================
    void CanvasComponent::paint (juce::Graphics& g)
    {
        if (onPaint)
            onPaint (g, *this);
    }
} // namespace gui