#include "Font.hpp"

#include <juce_graphics/juce_graphics.h>
namespace mc::lua::bindings {
auto juce_Font(sol::table& state) -> void
{

    // clang-format off

    state.new_enum("FontStyleFlags",
        "plain",
            juce::Font::plain,
        "bold",
            juce::Font::bold,
        "italic",
            juce::Font::italic,
        "underlined",
            juce::Font::underlined
    );

    auto font = state.new_usertype<juce::Font>("Font");
    font["new"] = sol::factories(
        [](float height) { return juce::Font { height }; },
        [](float height, int flags) { return juce::Font { height, flags }; }
    );

    // clang-format on

    font["setTypefaceName"]    = &juce::Font::setTypefaceName;
    font["getTypefaceName"]    = &juce::Font::getTypefaceName;
    font["getTypefaceStyle"]   = &juce::Font::getTypefaceStyle;
    font["setTypefaceStyle"]   = &juce::Font::setTypefaceStyle;
    font["withTypefaceStyle"]  = &juce::Font::withTypefaceStyle;
    font["getAvailableStyles"] = &juce::Font::getAvailableStyles;
}
} // namespace mc::lua::bindings
