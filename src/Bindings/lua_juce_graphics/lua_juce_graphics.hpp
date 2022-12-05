/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_graphics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_graphics
    description:        Lua/Sol2 bindings for juce_graphics
    dependencies:       lua_juce_sol2, juce_graphics
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_GRAPHICS
    #define USE_LUA_JUCE_GRAPHICS
#endif

#include <juce_graphics/juce_graphics.h>
#include <lua_juce_sol2/lua_juce_sol2.hpp>

#include "colour/Colour.hpp"
#include "colour/ColourGradient.hpp"
#include "colour/Colours.hpp"
#include "contexts/Graphics.hpp"
#include "font/Font.hpp"
#include "geometry/AffineTransform.hpp"
#include "geometry/Line.hpp"
#include "geometry/Path.hpp"
#include "geometry/Point.hpp"
#include "geometry/Rectangle.hpp"
#include "images/Image.hpp"
#include "images/ImageCache.hpp"
#include "placement/Justification.hpp"
