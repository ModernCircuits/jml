#include "ComponentListener.hpp"

namespace mc::lua::bindings {
namespace {
struct LuaComponentListener final : juce::ComponentListener
{
    LuaComponentListener()           = default;
    ~LuaComponentListener() override = default;

    auto componentMovedOrResized(juce::Component& component, bool wasMoved, bool wasResized) -> void override
    {
        if (not lua_componentMovedOrResized.valid()) { return; }
        lua_componentMovedOrResized(std::ref(*this), component, wasMoved, wasResized);
    }

    auto componentBroughtToFront(juce::Component& component) -> void override
    {
        if (not lua_componentBroughtToFront.valid()) { return; }
        lua_componentBroughtToFront(std::ref(*this), component);
    }

    auto componentVisibilityChanged(juce::Component& component) -> void override
    {
        if (not lua_componentVisibilityChanged.valid()) { return; }
        lua_componentVisibilityChanged(std::ref(*this), component);
    }

    auto componentChildrenChanged(juce::Component& component) -> void override
    {
        if (not lua_componentChildrenChanged.valid()) { return; }
        lua_componentChildrenChanged(std::ref(*this), component);
    }

    auto componentParentHierarchyChanged(juce::Component& component) -> void override
    {
        if (not lua_componentParentHierarchyChanged.valid()) { return; }
        lua_componentParentHierarchyChanged(std::ref(*this), component);
    }

    auto componentNameChanged(juce::Component& component) -> void override
    {
        if (not lua_componentNameChanged.valid()) { return; }
        lua_componentNameChanged(std::ref(*this), component);
    }

    auto componentBeingDeleted(juce::Component& component) -> void override
    {
        if (not lua_componentBeingDeleted.valid()) { return; }
        lua_componentBeingDeleted(std::ref(*this), component);
    }

    auto componentEnablementChanged(juce::Component& component) -> void override
    {
        if (not lua_componentEnablementChanged.valid()) { return; }
        lua_componentEnablementChanged(std::ref(*this), component);
    }

    sol::safe_function lua_componentMovedOrResized;
    sol::safe_function lua_componentBroughtToFront;
    sol::safe_function lua_componentVisibilityChanged;
    sol::safe_function lua_componentChildrenChanged;
    sol::safe_function lua_componentParentHierarchyChanged;
    sol::safe_function lua_componentNameChanged;
    sol::safe_function lua_componentBeingDeleted;
    sol::safe_function lua_componentEnablementChanged;
};
} // namespace
auto juce_ComponentListener(sol::table& state) -> void
{
    auto cl                               = state.new_usertype<juce::ComponentListener>("InternalComponentListener", sol::no_constructor);
    cl["componentMovedOrResized"]         = &juce::ComponentListener::componentMovedOrResized;
    cl["componentBroughtToFront"]         = &juce::ComponentListener::componentBroughtToFront;
    cl["componentVisibilityChanged"]      = &juce::ComponentListener::componentVisibilityChanged;
    cl["componentChildrenChanged"]        = &juce::ComponentListener::componentChildrenChanged;
    cl["componentParentHierarchyChanged"] = &juce::ComponentListener::componentParentHierarchyChanged;
    cl["componentNameChanged"]            = &juce::ComponentListener::componentNameChanged;
    cl["componentBeingDeleted"]           = &juce::ComponentListener::componentBeingDeleted;
    cl["componentEnablementChanged"]      = &juce::ComponentListener::componentEnablementChanged;

    auto luaCL = state.new_usertype<LuaComponentListener>(       //
        "ComponentListener",                                     //
        sol::constructors<LuaComponentListener()>(),             //
        sol::base_classes, sol::bases<juce::ComponentListener>() //
    );

    luaCL["componentMovedOrResized"]         = &LuaComponentListener::lua_componentMovedOrResized;
    luaCL["componentBroughtToFront"]         = &LuaComponentListener::lua_componentBroughtToFront;
    luaCL["componentVisibilityChanged"]      = &LuaComponentListener::lua_componentVisibilityChanged;
    luaCL["componentChildrenChanged"]        = &LuaComponentListener::lua_componentChildrenChanged;
    luaCL["componentParentHierarchyChanged"] = &LuaComponentListener::lua_componentParentHierarchyChanged;
    luaCL["componentNameChanged"]            = &LuaComponentListener::lua_componentNameChanged;
    luaCL["componentBeingDeleted"]           = &LuaComponentListener::lua_componentBeingDeleted;
    luaCL["componentEnablementChanged"]      = &LuaComponentListener::lua_componentEnablementChanged;
}
} // namespace mc::lua::bindings
