#include "String.hpp"

#include <juce_core/juce_core.h>

auto juce_String(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::String>("String",
        sol::constructors<juce::String(), juce::String(char const*)>()
    );
    // clang-format on
}