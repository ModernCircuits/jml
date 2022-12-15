#include "Button.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

SOL_BASE_CLASSES(juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

namespace mc::lua::bindings {
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

    button["onClick"]   = &juce::Button::onClick;
    button["getBounds"] = &juce::Component::getBounds;
    button["getWidth"]  = &juce::Component::getWidth;
    button["getHeight"] = &juce::Component::getHeight;
    button["getX"]      = &juce::Component::getX;
    button["getY"]      = &juce::Component::getY;
}
} // namespace mc::lua::bindings
