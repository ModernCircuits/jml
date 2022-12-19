#include "ToggleButton.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_ToggleButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ToggleButton>("ToggleButton",
        sol::constructors<
            juce::ToggleButton(),
            juce::ToggleButton(juce::String const&)
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

    button["changeWidthToFitText"] = &juce::ToggleButton::changeWidthToFitText;
}
} // namespace mc::lua::bindings
