#pragma once

#include "Sol3.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct LuaListBoxModel final : juce::ListBoxModel {
    LuaListBoxModel()           = default;
    ~LuaListBoxModel() override = default;

    auto getNumRows() -> int override
    {
        if (lua_getNumRows.valid()) { return lua_getNumRows(self()); }
        return 0;
    }

    auto paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) -> void override
    {
        if (lua_paintListBoxItem.valid()) { lua_paintListBoxItem(self(), rowNumber, std::ref(g), width, height, rowIsSelected); }
    }

    auto refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) -> juce::Component* override
    {
        if (lua_refreshComponentForRow.valid()) { lua_refreshComponentForRow(self(), rowNumber, isRowSelected, existingComponentToUpdate); }
        return juce::ListBoxModel::refreshComponentForRow(rowNumber, isRowSelected, existingComponentToUpdate);
    }

    auto getNameForRow(int rowNumber) -> juce::String override
    {
        if (lua_getNameForRow.valid()) { return lua_getNameForRow(self(), rowNumber); }
        return juce::ListBoxModel::getNameForRow(rowNumber);
    }

    auto listBoxItemClicked(int row, const juce::MouseEvent& event) -> void override
    {
        if (lua_listBoxItemClicked.valid()) { lua_listBoxItemClicked(self(), row, std::cref(event)); }
        return juce::ListBoxModel::listBoxItemClicked(row, event);
    }

    auto listBoxItemDoubleClicked(int row, const juce::MouseEvent& event) -> void override
    {
        if (lua_listBoxItemDoubleClicked.valid()) { lua_listBoxItemDoubleClicked(self(), row, std::cref(event)); }
        return juce::ListBoxModel::listBoxItemDoubleClicked(row, event);
    }

    auto backgroundClicked(const juce::MouseEvent& event) -> void override
    {
        if (lua_backgroundClicked.valid()) { lua_backgroundClicked(self(), std::cref(event)); }
        return juce::ListBoxModel::backgroundClicked(event);
    }

    auto selectedRowsChanged(int lastRowSelected) -> void override
    {
        if (lua_selectedRowsChanged.valid()) { lua_selectedRowsChanged(self(), lastRowSelected); }
        return juce::ListBoxModel::selectedRowsChanged(lastRowSelected);
    }

    auto deleteKeyPressed(int lastRowSelected) -> void override
    {
        if (lua_deleteKeyPressed.valid()) { lua_deleteKeyPressed(self(), lastRowSelected); }
        return juce::ListBoxModel::deleteKeyPressed(lastRowSelected);
    }

    auto returnKeyPressed(int lastRowSelected) -> void override
    {
        if (lua_returnKeyPressed.valid()) { lua_returnKeyPressed(self(), lastRowSelected); }
        return juce::ListBoxModel::returnKeyPressed(lastRowSelected);
    }

    auto listWasScrolled() -> void override
    {
        if (lua_listWasScrolled.valid()) { lua_listWasScrolled(self()); }
        return juce::ListBoxModel::listWasScrolled();
    }

    auto getDragSourceDescription(const juce::SparseSet<int>& rowsToDescribe) -> juce::var override
    {
        if (lua_getDragSourceDescription.valid()) { return lua_getDragSourceDescription(self(), std::cref(rowsToDescribe)); }
        return juce::ListBoxModel::getDragSourceDescription(rowsToDescribe);
    }

    auto getTooltipForRow(int row) -> juce::String override
    {
        if (lua_getTooltipForRow.valid()) { return lua_getTooltipForRow(self(), row); }
        return juce::ListBoxModel::getTooltipForRow(row);
    }

    auto getMouseCursorForRow(int row) -> juce::MouseCursor override
    {
        if (lua_getMouseCursorForRow.valid()) { return lua_getMouseCursorForRow(self(), row); }
        return juce::ListBoxModel::getMouseCursorForRow(row);
    }

    auto self() -> std::reference_wrapper<LuaListBoxModel> { return std::ref(*this); }

    sol::safe_function lua_getNumRows;
    sol::safe_function lua_paintListBoxItem;
    sol::safe_function lua_refreshComponentForRow;
    sol::safe_function lua_getNameForRow;
    sol::safe_function lua_listBoxItemClicked;
    sol::safe_function lua_listBoxItemDoubleClicked;
    sol::safe_function lua_backgroundClicked;
    sol::safe_function lua_selectedRowsChanged;
    sol::safe_function lua_deleteKeyPressed;
    sol::safe_function lua_returnKeyPressed;
    sol::safe_function lua_listWasScrolled;
    sol::safe_function lua_getDragSourceDescription;
    sol::safe_function lua_getTooltipForRow;
    sol::safe_function lua_getMouseCursorForRow;
};

SOL_BASE_CLASSES(LuaListBoxModel, juce::ListBoxModel);
SOL_DERIVED_CLASSES(juce::ListBoxModel, LuaListBoxModel);

auto juce_ListBoxModel(sol::table& state) -> void;
