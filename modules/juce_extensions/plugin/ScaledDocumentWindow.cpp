#include "ScaledDocumentWindow.h"

namespace plugin 
{
ScaledDocumentWindow::ScaledDocumentWindow (juce::String title, 
                                            juce::Colour backgroundColour, 
                                            float scale) 
    : DocumentWindow (title, backgroundColour, 7)
    , desktopScale (scale) 
{}

float ScaledDocumentWindow::getDesktopScaleFactor() const 
{
    return juce::Desktop::getInstance().getGlobalScaleFactor() * desktopScale; 
}

void ScaledDocumentWindow::closeButtonPressed() 
{
    if (onCloseButtonPressed) 
        onCloseButtonPressed(); 
}
} // namespace plugin