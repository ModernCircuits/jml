#include "TextButton.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

SOL_BASE_CLASSES(juce::TextButton, juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);
SOL_DERIVED_CLASSES(juce::Button, juce::TextButton);

auto juce_TextButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::TextButton>("TextButton",
        sol::factories(
            [] { return std::make_shared<juce::TextButton>(); },
            [](juce::String const& txt) { return std::make_shared<juce::TextButton>(txt); },
            [](juce::String const& txt,juce::String const& tool) { return std::make_shared<juce::TextButton>(txt,tool); }
        ),
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

    // button["onClick"] = &juce::Button::onClick;
}
