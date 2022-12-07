/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_core
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_core
    description:        Lua/Sol2 bindings for juce_core
    dependencies:       lua_juce_sol2, juce_core
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_CORE
    #define USE_LUA_JUCE_CORE
#endif

#include <juce_core/juce_core.h>
#include <lua_juce_sol2/lua_juce_sol2.hpp>

template<>
struct sol::is_container<juce::String> : std::false_type
{};

#include "containers/Array.hpp"
#include "files/File.hpp"
#include "maths/BigInteger.hpp"
#include "maths/Int.hpp"
#include "maths/MathConstants.hpp"
#include "maths/NormalisableRange.hpp"
#include "maths/Random.hpp"
#include "maths/Range.hpp"
#include "maths/StatisticsAccumulator.hpp"
#include "misc/Result.hpp"
#include "misc/Uuid.hpp"
#include "network/IPAddress.hpp"
#include "text/String.hpp"
#include "text/StringArray.hpp"
