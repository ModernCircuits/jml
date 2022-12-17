/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_gui_basics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_gui_basics
    description:        Lua/Sol2 bindings for juce_gui_basics
    dependencies:       lua_juce_graphics, juce_gui_basics
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_GUI_BASICS
    #define USE_LUA_JUCE_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <lua_juce_graphics/lua_juce_graphics.hpp>

#include "buttons/Button.hpp"
#include "buttons/TextButton.hpp"
#include "components/Component.hpp"
#include "components/LuaComponent.hpp"
#include "layout/Grid.hpp"
#include "lookandfeel/LookAndFeel.hpp"
#include "lookandfeel/LookAndFeel_V4.hpp"
#include "lookandfeel/LuaLookAndFeel_V4.hpp"
#include "mouse/MouseEvent.hpp"
#include "mouse/MouseWheelDetails.hpp"
#include "widgets/ComboBox.hpp"
#include "widgets/Label.hpp"
#include "widgets/ListBox.hpp"
#include "widgets/ListBoxModel.hpp"
#include "widgets/Slider.hpp"
