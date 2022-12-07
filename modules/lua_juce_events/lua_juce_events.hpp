/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_events
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       lua_juce_sol2, juce_events
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_EVENTS
    #define USE_LUA_JUCE_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <lua_juce_sol2/lua_juce_sol2.hpp>

#include "timers/LuaTimer.hpp"
#include "timers/Timer.hpp"
