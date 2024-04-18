#pragma once

#if 0
 BEGIN_JUCE_MODULE_DECLARATION
 
 ID:               juce_extensions
 vendor:           Jake Tyler
 version:          0.0.1
 name:             juce_extensions
 description:      juce_extensions
 license:          GPL/Commercial
 dependencies:     juce_audio_utils, juce_audio_processors
 
 END_JUCE_MODULE_DECLARATION
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>


// gui
#include "gui/CanvasComponent.h"

// plugin
#include "plugin/AudioProcessor.h"
#include "plugin/AudioProcessorEditor.h"
#include "plugin/PluginEditorComponent.h"
#include "plugin/ScaledDocumentWindow.h"

// tools
#include "tools/Timer.h"