/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_bindings
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       lua_juce_core, lua_juce_events, lua_juce_graphics, lua_juce_gui_basics
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_BINDINGS
    #define USE_LUA_JUCE_BINDINGS
#endif

#include <lua_juce_core/lua_juce_core.hpp>
#include <lua_juce_events/lua_juce_events.hpp>
#include <lua_juce_graphics/lua_juce_graphics.hpp>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>

namespace mc::lua::bindings {
auto allJuceModules(sol::state& lua) -> void;
}
