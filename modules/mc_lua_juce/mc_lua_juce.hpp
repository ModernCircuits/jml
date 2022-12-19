/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lua_juce
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       mc_lua_juce_core, mc_lua_juce_data_structures, mc_lua_juce_events, mc_lua_juce_graphics, mc_lua_juce_gui_basics
    website:            http://github.com/ModernCircuits/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LUA_JUCE
    #define USE_MC_LUA_JUCE
#endif

#include <mc_lua_juce_core/mc_lua_juce_core.hpp>
#include <mc_lua_juce_data_structures/mc_lua_juce_data_structures.hpp>
#include <mc_lua_juce_events/mc_lua_juce_events.hpp>
#include <mc_lua_juce_graphics/mc_lua_juce_graphics.hpp>
#include <mc_lua_juce_gui_basics/mc_lua_juce_gui_basics.hpp>

namespace mc::lua::bindings {
auto allJuceModules(sol::state& lua) -> void;
}
