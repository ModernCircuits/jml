#include "LuaComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct LuaComponent final : juce::Component {
    LuaComponent()           = default;
    ~LuaComponent() override = default;

    // juce::Component
    sol::function lua_paint;
    sol::function lua_resized;

    // juce::MouseListener
    sol::function lua_mouseMove;
    sol::function lua_mouseEnter;
    sol::function lua_mouseExit;
    sol::function lua_mouseDown;
    sol::function lua_mouseDrag;
    sol::function lua_mouseUp;
    sol::function lua_mouseDoubleClick;
    sol::function lua_mouseWheelMove;
    sol::function lua_mouseMagnify;

private:
    auto self() -> std::reference_wrapper<LuaComponent> { return std::ref(*this); }

    // juce::Component
    auto paint(juce::Graphics& g) -> void override
    {
        if (lua_paint.valid()) { lua_paint(self(), std::ref(g)); }
    }

    auto resized() -> void override
    {
        if (lua_resized.valid()) { lua_resized(self()); }
    }

    // juce::MouseListener
    auto mouseMove(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseMove.valid()) { lua_mouseMove(self(), std::cref(event)); }
    }
    auto mouseEnter(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseEnter.valid()) { lua_mouseEnter(self(), std::cref(event)); }
    }
    auto mouseExit(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseExit.valid()) { lua_mouseExit(self(), std::cref(event)); }
    }
    auto mouseDown(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDown.valid()) { lua_mouseDown(self(), std::cref(event)); }
    }
    auto mouseDrag(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDrag.valid()) { lua_mouseDrag(self(), std::cref(event)); }
    }
    auto mouseUp(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseUp.valid()) { lua_mouseUp(self(), std::cref(event)); }
    }
    auto mouseDoubleClick(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDoubleClick.valid()) { lua_mouseDoubleClick(self(), std::cref(event)); }
    }
    auto mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void override
    {
        if (lua_mouseWheelMove.valid()) { lua_mouseWheelMove(self(), std::cref(event), std::cref(wheel)); }
    }
    auto mouseMagnify(juce::MouseEvent const& event, float scaleFactor) -> void override
    {
        if (lua_mouseMagnify.valid()) { lua_mouseMagnify(self(), std::cref(event), scaleFactor); }
    }
};

auto juce_LuaComponent(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<LuaComponent>("LuaComponent",
	    sol::constructors<LuaComponent()>(),
        sol::base_classes, sol::bases<juce::Component>(),
        "paint",
        &LuaComponent::lua_paint,
        "resized",
        &LuaComponent::lua_resized,
        "mouseMove",
        &LuaComponent::lua_mouseMove,
        "mouseEnter",
        &LuaComponent::lua_mouseEnter,
        "mouseExit",
        &LuaComponent::lua_mouseExit,
        "mouseDown",
        &LuaComponent::lua_mouseDown,
        "mouseDrag",
        &LuaComponent::lua_mouseDrag,
        "mouseUp",
        &LuaComponent::lua_mouseUp,
        "mouseDoubleClick",
        &LuaComponent::lua_mouseDoubleClick,
        "mouseWheelMove",
        &LuaComponent::lua_mouseWheelMove,
        "mouseMagnify",
        &LuaComponent::lua_mouseMagnify
    );
    // clang-format on
}