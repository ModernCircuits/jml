#include "Int.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_Int(sol::table& state) -> void
{
    state.new_usertype<juce::int8>("int8", sol::default_constructor);
    state.new_usertype<juce::int16>("int16", sol::default_constructor);
    state.new_usertype<juce::int32>("int32", sol::default_constructor);
    state.new_usertype<juce::int64>("int64", sol::default_constructor);

    state.new_usertype<juce::uint8>("uint8", sol::default_constructor);
    state.new_usertype<juce::uint16>("uint16", sol::default_constructor);
    state.new_usertype<juce::uint32>("uint32", sol::default_constructor);
    state.new_usertype<juce::uint64>("uint64", sol::default_constructor);

    state.new_usertype<juce::pointer_sized_int>("pointer_sized_int", sol::default_constructor);
    state.new_usertype<juce::pointer_sized_uint>("pointer_sized_uint", sol::default_constructor);
}
} // namespace mc::lua::bindings
