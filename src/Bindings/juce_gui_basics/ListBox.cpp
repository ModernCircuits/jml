#include "ListBox.hpp"

#include "ListBoxModel.hpp"

struct LuaListBox final : juce::ListBox {
    LuaListBox() : juce::ListBox({}, nullptr) { }
    ~LuaListBox() override { setModel(nullptr); }

    auto internal_setModel(std::shared_ptr<LuaListBoxModel> m) -> void
    {
        if (m == _model) { return; }
        if (m == nullptr) { return; }
        setModel(m.get());
        _model = std::move(m);
    }

private:
    std::shared_ptr<LuaListBoxModel> _model;
};

auto juce_ListBox(sol::table& state) -> void
{
    // clang-format off
    auto listBox = state.new_usertype<juce::ListBox>("InternalListBox",
        sol::no_construction{},
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    listBox["getModel"]                       = &juce::ListBox::getModel;
    listBox["updateContent"]                  = &juce::ListBox::updateContent;
    listBox["setMultipleSelectionEnabled"]    = &juce::ListBox::setMultipleSelectionEnabled;
    listBox["setClickingTogglesRowSelection"] = &juce::ListBox::setClickingTogglesRowSelection;
    listBox["setRowSelectedOnMouseDown"]      = &juce::ListBox::setRowSelectedOnMouseDown;
    listBox["setMouseMoveSelectsRows"]        = &juce::ListBox::setMouseMoveSelectsRows;
    listBox["selectRow"]                      = &juce::ListBox::selectRow;
    listBox["selectRangeOfRows"]              = &juce::ListBox::selectRangeOfRows;
    listBox["deselectRow"]                    = &juce::ListBox::deselectRow;
    listBox["deselectAllRows"]                = &juce::ListBox::deselectAllRows;
    listBox["flipRowSelection"]               = &juce::ListBox::flipRowSelection;
    listBox["getSelectedRows"]                = &juce::ListBox::getSelectedRows;
    listBox["isRowSelected"]                  = &juce::ListBox::isRowSelected;
    listBox["getNumSelectedRows"]             = &juce::ListBox::getNumSelectedRows;
    listBox["getSelectedRow"]                 = &juce::ListBox::getSelectedRow;
    listBox["getLastRowSelected"]             = &juce::ListBox::getLastRowSelected;
    listBox["selectRowsBasedOnModifierKeys"]  = &juce::ListBox::selectRowsBasedOnModifierKeys;
    listBox["setVerticalPosition"]            = &juce::ListBox::setVerticalPosition;
    listBox["getVerticalPosition"]            = &juce::ListBox::getVerticalPosition;
    listBox["scrollToEnsureRowIsOnscreen"]    = &juce::ListBox::scrollToEnsureRowIsOnscreen;
    listBox["getVerticalScrollBar"]           = &juce::ListBox::getVerticalScrollBar;
    listBox["getHorizontalScrollBar"]         = &juce::ListBox::getHorizontalScrollBar;
    listBox["getRowContainingPosition"]       = &juce::ListBox::getRowContainingPosition;
    listBox["getInsertionIndexForPosition"]   = &juce::ListBox::getInsertionIndexForPosition;
    listBox["getRowPosition"]                 = &juce::ListBox::getRowPosition;
    listBox["getComponentForRowNumber"]       = &juce::ListBox::getComponentForRowNumber;
    listBox["getRowNumberOfComponent"]        = &juce::ListBox::getRowNumberOfComponent;
    listBox["getVisibleRowWidth"]             = &juce::ListBox::getVisibleRowWidth;
    listBox["setRowHeight"]                   = &juce::ListBox::setRowHeight;
    listBox["getRowHeight"]                   = &juce::ListBox::getRowHeight;
    listBox["getNumRowsOnScreen"]             = &juce::ListBox::getNumRowsOnScreen;
    listBox["setOutlineThickness"]            = &juce::ListBox::setOutlineThickness;
    listBox["getOutlineThickness"]            = &juce::ListBox::getOutlineThickness;
    listBox["getHeaderComponent"]             = &juce::ListBox::getHeaderComponent;
    listBox["setMinimumContentWidth"]         = &juce::ListBox::setMinimumContentWidth;
    listBox["getVisibleContentWidth"]         = &juce::ListBox::getVisibleContentWidth;
    listBox["repaintRow"]                     = &juce::ListBox::repaintRow;
    listBox["getViewport"]                    = &juce::ListBox::getViewport;
    // listBox["createSnapshotOfRows"]           = &juce::ListBox::createSnapshotOfRows;

    listBox["setHeaderComponent"] = [](juce::ListBox* lb, std::unique_ptr<juce::Component>& h) { lb->setHeaderComponent(std::move(h)); };
    listBox["setSelectedRows"]    = sol::overload(
        [](juce::ListBox* lb, juce::SparseSet<int> const& rows) { lb->setSelectedRows(rows, juce::NotificationType::sendNotification); },
        [](juce::ListBox* lb, juce::SparseSet<int> const& rows, juce::NotificationType n) { lb->setSelectedRows(rows, n); });

    // clang-format off
    auto luaListBox = state.new_usertype<LuaListBox>("ListBox",
        sol::factories([] { return std::make_shared<LuaListBox>(); }),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient,
            juce::ListBox
        >()
    );
    // clang-format on

    luaListBox["setModel"] = &LuaListBox::internal_setModel;
}
