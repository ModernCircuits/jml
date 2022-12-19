/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lua_juce_gui_extra
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_gui_extra
    description:        Lua/Sol2 bindings for juce_gui_extra
    dependencies:       mc_lua_juce_gui_basics, juce_gui_extra
    website:            http://github.com/ModernCircuits/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LUA_JUCE_GUI_EXTRA
    #define USE_MC_LUA_JUCE_GUI_EXTRA
#endif

#include <juce_gui_extra/juce_gui_extra.h>
#include <mc_lua_juce_gui_basics/mc_lua_juce_gui_basics.hpp>

#include "code_editor/CPlusPlusCodeTokeniser.hpp"
#include "code_editor/CodeDocument.hpp"
#include "code_editor/CodeTokeniser.hpp"
#include "code_editor/LuaTokeniser.hpp"
#include "code_editor/XmlTokeniser.hpp"
