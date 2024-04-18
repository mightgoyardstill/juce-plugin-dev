#include "AudioProcessor.h"
#include "AudioProcessorEditor.h"

namespace plugin
{
//==============================================================================
AudioProcessorEditor::AudioProcessorEditor (AudioProcessor& p) : juce::AudioProcessorEditor (&p)
{
}


AudioProcessorEditor::~AudioProcessorEditor() 
{
}

//==============================================================================
void AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (backgroundColour);
}

//==============================================================================
void AudioProcessorEditor::setUsingNativeTitleBar (bool useNativeTitleBar)
{
    if (juce::JUCEApplicationBase::isStandaloneApp())
    {
        if (auto* mainWindow = dynamic_cast<juce::DocumentWindow*> (juce::TopLevelWindow::getTopLevelWindow(0)))
            mainWindow->setUsingNativeTitleBar (useNativeTitleBar);
    }
}

void AudioProcessorEditor::setBackgroundColour (juce::Colour colour) 
{
    backgroundColour = colour; 
}


void AudioProcessorEditor::addAndMakeVisible(const std::initializer_list<Component*>& components)
{
    for (auto* comp : components)
        juce::AudioProcessorEditor::addAndMakeVisible(comp);
}

} // namespace pluginextensions