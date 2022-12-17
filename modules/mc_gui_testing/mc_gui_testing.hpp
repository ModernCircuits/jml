/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_gui_testing
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       mc_gui_extra
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GUI_TESTING
    #define USE_MC_GUI_TESTING
#endif

#include <mc_gui_extra/mc_gui_extra.hpp>

#include "message/button.hpp"
#include "message/component.hpp"
