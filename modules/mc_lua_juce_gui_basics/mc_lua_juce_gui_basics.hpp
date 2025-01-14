/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lua_juce_gui_basics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_gui_basics
    description:        Lua/Sol2 bindings for juce_gui_basics
    dependencies:       mc_lua_juce_graphics, mc_lua_juce_data_structures, juce_gui_basics
    website:            http://github.com/ModernCircuits/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LUA_JUCE_GUI_BASICS
    #define USE_MC_LUA_JUCE_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_lua_juce_data_structures/mc_lua_juce_data_structures.hpp>
#include <mc_lua_juce_graphics/mc_lua_juce_graphics.hpp>

#include "buttons/ArrowButton.hpp"
#include "buttons/Button.hpp"
#include "buttons/HyperlinkButton.hpp"
#include "buttons/ImageButton.hpp"
#include "buttons/ShapeButton.hpp"
#include "buttons/TextButton.hpp"
#include "buttons/ToggleButton.hpp"
#include "components/Component.hpp"
#include "components/ComponentListener.hpp"
#include "components/LuaComponent.hpp"
#include "layout/Grid.hpp"
#include "lookandfeel/LookAndFeel.hpp"
#include "lookandfeel/LookAndFeel_V4.hpp"
#include "lookandfeel/LuaLookAndFeel_V4.hpp"
#include "mouse/MouseEvent.hpp"
#include "mouse/MouseWheelDetails.hpp"
#include "widgets/ComboBox.hpp"
#include "widgets/ImageComponent.hpp"
#include "widgets/Label.hpp"
#include "widgets/ListBox.hpp"
#include "widgets/ListBoxModel.hpp"
#include "widgets/Slider.hpp"
#include "widgets/TextEditor.hpp"
#include "widgets/TreeView.hpp"
