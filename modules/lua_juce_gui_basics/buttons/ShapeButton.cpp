#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_ShapeButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ShapeButton>("ShapeButton",
        sol::constructors<
            juce::ShapeButton(juce::String const&, juce::Colour, juce::Colour, juce::Colour)
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

    button["setShape"]           = &juce::ShapeButton::setShape;
    button["setColours"]         = &juce::ShapeButton::setColours;
    button["setOnColours"]       = &juce::ShapeButton::setOnColours;
    button["shouldUseOnColours"] = &juce::ShapeButton::shouldUseOnColours;
    button["setOutline"]         = &juce::ShapeButton::setOutline;
    button["setBorderSize"]      = &juce::ShapeButton::setBorderSize;
}
} // namespace mc::lua::bindings
