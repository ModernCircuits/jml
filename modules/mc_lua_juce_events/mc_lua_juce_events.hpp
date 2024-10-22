/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lua_juce_events
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       mc_lua_juce_core, juce_events
    website:            http://github.com/ModernCircuits/jml
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LUA_JUCE_EVENTS
    #define USE_MC_LUA_JUCE_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <mc_lua_juce_core/mc_lua_juce_core.hpp>

#include "timers/LuaTimer.hpp"
#include "timers/Timer.hpp"
