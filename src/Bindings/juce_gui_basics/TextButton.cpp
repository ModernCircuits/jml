#include "TextButton.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_TextButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::TextButton>("TextButton",
        sol::constructors<
            juce::TextButton(),
            juce::TextButton(juce::String const&),
            juce::TextButton(juce::String const&, juce::String const&)
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

    button["onClick"] = &juce::Button::onClick;
}
