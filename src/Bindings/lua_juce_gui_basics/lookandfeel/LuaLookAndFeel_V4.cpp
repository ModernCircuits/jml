#include "LuaLookAndFeel_V4.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct LuaLookAndFeel_V4 final : juce::LookAndFeel_V4 {
    LuaLookAndFeel_V4()           = default;
    ~LuaLookAndFeel_V4() override = default;

    // juce::LookAndFeel_V4
    sol::safe_function lua_getTextButtonFont;
    sol::safe_function lua_drawButtonBackground;
    sol::safe_function lua_drawToggleButton;

    auto dummy() -> void { juce::ignoreUnused(this); }

private:
    auto self() -> std::reference_wrapper<LuaLookAndFeel_V4> { return std::ref(*this); }

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
            lua_drawButtonBackground(self(), std::ref(g), &btn, color, isHighlighted, isDown);
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

auto juce_LuaLookAndFeel_V4(sol::table& state) -> void
{
    // clang-format off
    auto lnf = state.new_usertype<LuaLookAndFeel_V4>("LookAndFeel_V4",
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

    lnf["getTextButtonFont"]    = &LuaLookAndFeel_V4::lua_getTextButtonFont;
    lnf["drawButtonBackground"] = &LuaLookAndFeel_V4::lua_drawButtonBackground;
    lnf["drawToggleButton"]     = &LuaLookAndFeel_V4::lua_drawToggleButton;
    lnf["dummy"]                = &LuaLookAndFeel_V4::dummy;
}
