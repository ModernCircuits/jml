#include "String.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_String(sol::table& state) -> void
{
    auto str = state.new_usertype<juce::String>("String", sol::constructors<juce::String(), juce::String(char const*)>());

    str["isEmpty"]    = &juce::String::isEmpty;
    str["isNotEmpty"] = &juce::String::isNotEmpty;
    str["clear"]      = &juce::String::clear;
    str["hashCode"]   = &juce::String::hashCode;
    str["hashCode64"] = &juce::String::hashCode64;
    str["hash"]       = &juce::String::hash;
    str["length"]     = &juce::String::length;
}
} // namespace mc::lua::bindings
