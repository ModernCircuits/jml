/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_core
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_core
    description:        Lua/Sol2 bindings for juce_core
    dependencies:       juce_core
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

#include <sol/sol.hpp>

namespace juce {

namespace lua_detail {
template<typename C>
struct has_toString
{
private:
    template<typename T>
    static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().toString()), juce::String>::type;

    template<typename>
    static constexpr auto check(...) -> std::false_type;

    using type = decltype(check<C>(0));

public:
    static constexpr bool value = type::value;
};
} // namespace lua_detail

template<typename T>
auto to_string(T const& val) -> std::enable_if_t<lua_detail::has_toString<T>::value, std::string>
{
    return val.toString().toStdString();
}

template<typename T>
auto to_string(T const& val) -> decltype(val.toStdString())
{
    return val.toStdString();
}
} // namespace juce


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
#include "time/PerformanceCounter.hpp"
#include "time/RelativeTime.hpp"
#include "time/Time.hpp"
