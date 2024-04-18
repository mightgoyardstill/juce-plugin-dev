#pragma once
#include "AudioProcessor.h"

namespace plugin
{
    //==============================================================================
    class AudioProcessorEditor  : public juce::AudioProcessorEditor
    {
    public:
        //==============================================================================
        explicit AudioProcessorEditor (AudioProcessor&);
        ~AudioProcessorEditor() override;

        //==============================================================================
        void paint (juce::Graphics&) override;
        
        //==============================================================================
        void setUsingNativeTitleBar (bool);
        void setBackgroundColour (juce::Colour);
        void addAndMakeVisible(const std::initializer_list<Component*>&);
    
    private:
        juce::Colour backgroundColour { getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId) };
    };

} // namespace plugin