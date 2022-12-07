/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_sol2
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Lua bindings for juce_sol2
    description:        Lua/Sol2 bindings for juce_sol2
    dependencies:       juce_core
    website:            http://github.com/ModernCircuits/juce-lua-bindings
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_SOL2
    #define USE_LUA_JUCE_SOL2
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
