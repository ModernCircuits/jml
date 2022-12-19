#include "ListBoxModel.hpp"
namespace mc::lua::bindings {

static auto juce_LuaListBoxModel(sol::table& state) -> void
{
    // clang-format off
    auto model = state.new_usertype<LuaListBoxModel>("ListBoxModel",
        sol::factories([] { return std::make_shared<LuaListBoxModel>(); }),
        sol::base_classes, sol::bases<juce::ListBoxModel>{}
    );
    // clang-format on

    model["getNumRows"]               = &LuaListBoxModel::lua_getNumRows;
    model["paintListBoxItem"]         = &LuaListBoxModel::lua_paintListBoxItem;
    model["refreshComponentForRow"]   = &LuaListBoxModel::lua_refreshComponentForRow;
    model["getNameForRow"]            = &LuaListBoxModel::lua_getNameForRow;
    model["listBoxItemClicked"]       = &LuaListBoxModel::lua_listBoxItemClicked;
    model["listBoxItemDoubleClicked"] = &LuaListBoxModel::lua_listBoxItemDoubleClicked;
    model["backgroundClicked"]        = &LuaListBoxModel::lua_backgroundClicked;
    model["selectedRowsChanged"]      = &LuaListBoxModel::lua_selectedRowsChanged;
    model["deleteKeyPressed"]         = &LuaListBoxModel::lua_deleteKeyPressed;
    model["returnKeyPressed"]         = &LuaListBoxModel::lua_returnKeyPressed;
    model["listWasScrolled"]          = &LuaListBoxModel::lua_listWasScrolled;
    model["getDragSourceDescription"] = &LuaListBoxModel::lua_getDragSourceDescription;
    model["getTooltipForRow"]         = &LuaListBoxModel::lua_getTooltipForRow;
    model["getMouseCursorForRow"]     = &LuaListBoxModel::lua_getMouseCursorForRow;
}

auto juce_ListBoxModel(sol::table& state) -> void
{
    auto model                        = state.new_usertype<juce::ListBoxModel>("InternalListBoxModel", sol::no_constructor);
    model["getNumRows"]               = &juce::ListBoxModel::getNumRows;
    model["paintListBoxItem"]         = &juce::ListBoxModel::paintListBoxItem;
    model["refreshComponentForRow"]   = &juce::ListBoxModel::refreshComponentForRow;
    model["getNameForRow"]            = &juce::ListBoxModel::getNameForRow;
    model["listBoxItemClicked"]       = &juce::ListBoxModel::listBoxItemClicked;
    model["listBoxItemDoubleClicked"] = &juce::ListBoxModel::listBoxItemDoubleClicked;
    model["backgroundClicked"]        = &juce::ListBoxModel::backgroundClicked;
    model["selectedRowsChanged"]      = &juce::ListBoxModel::selectedRowsChanged;
    model["deleteKeyPressed"]         = &juce::ListBoxModel::deleteKeyPressed;
    model["returnKeyPressed"]         = &juce::ListBoxModel::returnKeyPressed;
    model["listWasScrolled"]          = &juce::ListBoxModel::listWasScrolled;
    model["getDragSourceDescription"] = &juce::ListBoxModel::getDragSourceDescription;
    model["getTooltipForRow"]         = &juce::ListBoxModel::getTooltipForRow;
    model["getMouseCursorForRow"]     = &juce::ListBoxModel::getMouseCursorForRow;

    juce_LuaListBoxModel(state);
}
} // namespace mc::lua::bindings
