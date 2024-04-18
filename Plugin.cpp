#include <juce_extensions/juce_extensions.h>
#include "dev/Tools/GridStringInterpreter.h"

//==============================================================================
class Plugin : public plugin::AudioProcessor
{
    class WhiteNoiseTestGenerator
    {
    public:
        float getNextSample() { return juce::jmap (randomGenerator.nextFloat(), -1.0f, 1.0f); }
    private:
        juce::Random randomGenerator;
    };

    WhiteNoiseTestGenerator noiseGenerator;

public:
    //==============================================================================
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override
    {
        auto channelData = buffer.getWritePointer(0);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto& sampleData = channelData[sample];
            sampleData = noiseGenerator.getNextSample();
        }

        for (int index = 1; index < buffer.getNumChannels(); ++index)
            buffer.copyFrom (index, 0, channelData, buffer.getNumSamples());
    }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
};


//==============================================================================
class Editor : public plugin::AudioProcessorEditor
{
    Plugin& processorRef;
    tools::GridStringInterpreter interpreter;
    gui::CanvasComponent canvas;

public:
    //==============================================================================
    Editor (Plugin& p) : AudioProcessorEditor (p), processorRef (p)
    {
        juce::ignoreUnused (processorRef);

        canvas.onPaint = [] (juce::Graphics& g, juce::Component& c)
        {
            g.fillAll (juce::Colours::black);            
            g.setColour (juce::Colours::white);
            g.setFont (14.0f);         
            g.drawFittedText ("hello, world!", c.getLocalBounds(), juce::Justification::centred, 1);
        };

        auto layout =   
        R"(
            grid-template-columns: 1fr;
            grid-template-rows: 1fr;
            grid-template-areas: "main"
            grid-gap: 1px;
        )";
        
        interpreter.setLayout (layout, { { &canvas, "main" } } );
        
        addAndMakeVisible ({ &canvas });
        setUsingNativeTitleBar (true);
        setBackgroundColour (juce::Colours::darkgrey); 
        setResizable (true, true);
        setSize (360, 380);
    }

    //==============================================================================
    void resized() override { interpreter.performLayout (getLocalBounds().reduced (2)); }
};


//==============================================================================
// This is called by the plugin and creates a new instance of 
// the plugin's editor..
juce::AudioProcessorEditor* Plugin::createEditor()
{
    return new Editor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Plugin();
}