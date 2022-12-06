#include "LuaComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct LuaComponent final : juce::Component {
    LuaComponent()           = default;
    ~LuaComponent() override = default;

    // juce::Component
    sol::safe_function lua_paint;
    sol::safe_function lua_resized;

    // juce::MouseListener
    sol::safe_function lua_mouseMove;
    sol::safe_function lua_mouseEnter;
    sol::safe_function lua_mouseExit;
    sol::safe_function lua_mouseDown;
    sol::safe_function lua_mouseDrag;
    sol::safe_function lua_mouseUp;
    sol::safe_function lua_mouseDoubleClick;
    sol::safe_function lua_mouseWheelMove;
    sol::safe_function lua_mouseMagnify;

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

SOL_BASE_CLASSES(LuaComponent, juce::Component, juce::MouseListener);
SOL_DERIVED_CLASSES(juce::Component, LuaComponent);

auto juce_LuaComponent(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<LuaComponent>("Component",
        sol::constructors<LuaComponent()>(),
        sol::base_classes, sol::bases<juce::Component, juce::MouseListener>()
    );
    // clang-format on

    comp["paint"]            = &LuaComponent::lua_paint;
    comp["resized"]          = &LuaComponent::lua_resized;
    comp["mouseMove"]        = &LuaComponent::lua_mouseMove;
    comp["mouseEnter"]       = &LuaComponent::lua_mouseEnter;
    comp["mouseExit"]        = &LuaComponent::lua_mouseExit;
    comp["mouseDown"]        = &LuaComponent::lua_mouseDown;
    comp["mouseDrag"]        = &LuaComponent::lua_mouseDrag;
    comp["mouseUp"]          = &LuaComponent::lua_mouseUp;
    comp["mouseDoubleClick"] = &LuaComponent::lua_mouseDoubleClick;
    comp["mouseWheelMove"]   = &LuaComponent::lua_mouseWheelMove;
    comp["mouseMagnify"]     = &LuaComponent::lua_mouseMagnify;
}
