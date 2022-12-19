#include "ArrowButton.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_ArrowButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ArrowButton>("ArrowButton",
        sol::constructors<
            juce::ArrowButton(juce::String const&, float, juce::Colour)
        >(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::Button,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on
}
} // namespace mc::lua::bindings
