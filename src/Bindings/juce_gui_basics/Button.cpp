#include "Button.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_Button(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::Button>("Button",
        sol::no_constructor,
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    button["onClick"] = &juce::Button::onClick;
}
