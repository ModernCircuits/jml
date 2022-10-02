#include "LuaLookAndFeel.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct LuaLookAndFeel final : juce::LookAndFeel_V4 {
    LuaLookAndFeel()           = default;
    ~LuaLookAndFeel() override = default;

    // juce::LookAndFeel_V4
    sol::function lua_getTextButtonFont;
    sol::function lua_drawButtonBackground;
    sol::function lua_drawToggleButton;

private:
    auto self() -> std::reference_wrapper<LuaLookAndFeel> { return std::ref(*this); }

    // juce::Button
    auto getTextButtonFont(juce::TextButton& btn, int buttonHeight) -> juce::Font override
    {
        if (lua_getTextButtonFont.valid()) {
            return lua_getTextButtonFont(self(), std::ref(btn), buttonHeight);
        } else {
            return juce::LookAndFeel_V4::getTextButtonFont(btn, buttonHeight);
        }
    }

    auto drawButtonBackground(juce::Graphics& g, juce::Button& btn, juce::Colour const& color, bool isHighlighted, bool isDown)
        -> void override
    {
        if (lua_drawButtonBackground.valid()) {
            lua_drawButtonBackground(self(), &g, static_cast<juce::Component*>(&btn), std::cref(color), isHighlighted, isDown);
        } else {
            juce::LookAndFeel_V4::drawButtonBackground(g, btn, color, isHighlighted, isDown);
        }
    }

    auto drawToggleButton(juce::Graphics& g, juce::ToggleButton& btn, bool isHighlighted, bool isDown) -> void override
    {
        if (lua_drawToggleButton.valid()) {
            lua_drawToggleButton(self(), std::ref(g), std::ref(btn), isHighlighted, isDown);
        } else {
            juce::LookAndFeel_V4::drawToggleButton(g, btn, isHighlighted, isDown);
        }
    }
};

auto juce_LuaLookAndFeel(sol::table& state) -> void
{
    // clang-format off
    auto lnf = state.new_usertype<LuaLookAndFeel>("LuaLookAndFeel",
	    sol::default_constructor,
        sol::base_classes,
        sol::bases<
            juce::LookAndFeel,
            juce::LookAndFeel_V2,
            juce::LookAndFeel_V3,
            juce::LookAndFeel_V4
        >()
    );
    // clang-format on

    lnf["getTextButtonFont"]    = &LuaLookAndFeel::lua_getTextButtonFont;
    lnf["drawButtonBackground"] = &LuaLookAndFeel::lua_drawButtonBackground;
    lnf["drawToggleButton"]     = &LuaLookAndFeel::lua_drawToggleButton;
}