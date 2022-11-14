#pragma once

#include <sol/sol.hpp>

#include <juce_core/juce_core.h>

namespace juce {

namespace lua_detail {
template <typename C>
struct has_toString {
private:
    template <typename T>
    static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().toString()), juce::String>::type;

    template <typename>
    static constexpr auto check(...) -> std::false_type;

    using type = decltype(check<C>(0));

public:
    static constexpr bool value = type::value;
};
} // namespace lua_detail

template <typename T>
auto to_string(T const& val) -> std::enable_if_t<lua_detail::has_toString<T>::value, std::string>
{
    return val.toString().toStdString();
}

template <typename T>
auto to_string(T const& val) -> decltype(val.toStdString())
{
    return val.toStdString();
}
} // namespace juce

// template <>
// struct sol::stack::unqualified_getter<juce::String> {
//     static auto get(lua_State* L, int index, sol::stack::record& tracking) -> juce::String
//     {
//         tracking.use(1);
//         return juce::String { stack::get<const char*>(L, index) };
//     }
// };

// template <>
// struct sol::stack::unqualified_pusher<juce::String> {
//     static auto push(lua_State* L, juce::String const& str) -> int { return stack::push(L, str.getCharPointer()); }
// };

// template <>
// struct sol::lua_type_of<juce::String> : std::integral_constant<sol::type, sol::type::string> {
// };
