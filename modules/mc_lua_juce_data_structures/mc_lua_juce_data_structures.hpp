/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lua_juce_data_structures
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_data_structures
    description:        Lua/Sol2 bindings for juce_data_structures
    dependencies:       mc_lua_juce_events, juce_data_structures
    website:            http://github.com/ModernCircuits/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LUA_JUCE_DATA_STRUCTURES
    #define USE_MC_LUA_JUCE_DATA_STRUCTURES
#endif

#include <juce_data_structures/juce_data_structures.h>
#include <mc_lua_juce_events/mc_lua_juce_events.hpp>

#include "undomanager/UndoManager.hpp"
#include "undomanager/UndoableAction.hpp"
#include "values/ValueTree.hpp"
