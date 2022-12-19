#include "TreeView.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {

auto juce_TreeView(sol::table& state) -> void
{
    // clang-format off
    auto treeView = state.new_usertype<juce::TreeView>("TreeView",
        sol::constructors<juce::TreeView(juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::FileDragAndDropTarget,
            juce::DragAndDropTarget,
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    treeView["setRootItem"]                  = &juce::TreeView::setRootItem;
    treeView["getRootItem"]                  = &juce::TreeView::getRootItem;
    treeView["deleteRootItem"]               = &juce::TreeView::deleteRootItem;
    treeView["setRootItemVisible"]           = &juce::TreeView::setRootItemVisible;
    treeView["isRootItemVisible"]            = &juce::TreeView::isRootItemVisible;
    treeView["setDefaultOpenness"]           = &juce::TreeView::setDefaultOpenness;
    treeView["areItemsOpenByDefault"]        = &juce::TreeView::areItemsOpenByDefault;
    treeView["setMultiSelectEnabled"]        = &juce::TreeView::setMultiSelectEnabled;
    treeView["isMultiSelectEnabled"]         = &juce::TreeView::isMultiSelectEnabled;
    treeView["setOpenCloseButtonsVisible"]   = &juce::TreeView::setOpenCloseButtonsVisible;
    treeView["areOpenCloseButtonsVisible"]   = &juce::TreeView::areOpenCloseButtonsVisible;
    treeView["clearSelectedItems"]           = &juce::TreeView::clearSelectedItems;
    treeView["getNumSelectedItems"]          = &juce::TreeView::getNumSelectedItems;
    treeView["getSelectedItem"]              = &juce::TreeView::getSelectedItem;
    treeView["moveSelectedRow"]              = &juce::TreeView::moveSelectedRow;
    treeView["getNumRowsInTree"]             = &juce::TreeView::getNumRowsInTree;
    treeView["getItemOnRow"]                 = &juce::TreeView::getItemOnRow;
    treeView["getItemAt"]                    = &juce::TreeView::getItemAt;
    treeView["scrollToKeepItemVisible"]      = &juce::TreeView::scrollToKeepItemVisible;
    treeView["getViewport"]                  = &juce::TreeView::getViewport;
    treeView["getIndentSize"]                = &juce::TreeView::getIndentSize;
    treeView["setIndentSize"]                = &juce::TreeView::setIndentSize;
    treeView["findItemFromIdentifierString"] = &juce::TreeView::findItemFromIdentifierString;
    treeView["getItemComponent"]             = &juce::TreeView::getItemComponent;
    treeView["getOpennessState"]             = &juce::TreeView::getOpennessState;
    treeView["restoreOpennessState"]         = &juce::TreeView::restoreOpennessState;
}

} // namespace mc::lua::bindings
