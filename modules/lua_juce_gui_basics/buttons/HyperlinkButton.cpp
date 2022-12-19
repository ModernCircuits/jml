#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_HyperlinkButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::HyperlinkButton>("HyperlinkButton",
        sol::constructors<
            juce::HyperlinkButton(),
            juce::HyperlinkButton(juce::String const&, juce::URL const&)
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

    button["setFont"]              = &juce::HyperlinkButton::setFont;
    button["setURL"]               = &juce::HyperlinkButton::setURL;
    button["getURL"]               = &juce::HyperlinkButton::getURL;
    button["changeWidthToFitText"] = &juce::HyperlinkButton::changeWidthToFitText;
    button["setJustificationType"] = &juce::HyperlinkButton::setJustificationType;
    button["getJustificationType"] = &juce::HyperlinkButton::getJustificationType;
}
} // namespace mc::lua::bindings
