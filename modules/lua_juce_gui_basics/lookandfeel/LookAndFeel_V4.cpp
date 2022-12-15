#include "LookAndFeel_V4.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_LookAndFeel_V4(sol::table& state) -> void
{
    // clang-format off
    auto lnf = state.new_usertype<juce::LookAndFeel_V4>("InternalLookAndFeel_V4",
        sol::constructors<
            juce::LookAndFeel_V4(),
            juce::LookAndFeel_V4(juce::LookAndFeel_V4::ColourScheme)
        >(),
        sol::base_classes,
        sol::bases<
            juce::LookAndFeel,
            juce::LookAndFeel_V2,
            juce::LookAndFeel_V3
        >()
    );
    // clang-format on

    // lnf["setColourScheme"]         = juce::LookAndFeel_V4::setColourScheme;
    // lnf["getCurrentColourScheme"]  = juce::LookAndFeel_V4::getCurrentColourScheme;
    lnf["getDarkColourScheme"]     = juce::LookAndFeel_V4::getDarkColourScheme;
    lnf["getMidnightColourScheme"] = juce::LookAndFeel_V4::getMidnightColourScheme;
    lnf["getGreyColourScheme"]     = juce::LookAndFeel_V4::getGreyColourScheme;
    lnf["getLightColourScheme"]    = juce::LookAndFeel_V4::getLightColourScheme;
}
} // namespace mc::lua::bindings
