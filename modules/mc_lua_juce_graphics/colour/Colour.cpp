#include "Colour.hpp"

#include <juce_graphics/juce_graphics.h>

namespace mc::lua::bindings {
auto juce_Colour(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<juce::Colour>("Colour",
        sol::constructors<
            juce::Colour(),
            juce::Colour(juce::uint8, juce::uint8, juce::uint8, juce::uint8)
        >()
    );
    // clang-format on
}
} // namespace mc::lua::bindings
