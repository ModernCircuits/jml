#pragma once

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

template<typename TreeViewItemType>
inline auto getSelectedTreeViewItems(juce::TreeView& treeView) -> juce::OwnedArray<juce::ValueTree>
{
    juce::OwnedArray<juce::ValueTree> items;
    int const numSelected = treeView.getNumSelectedItems();

    for (int i = 0; i < numSelected; ++i) {
        if (auto* vti = dynamic_cast<TreeViewItemType*>(treeView.getSelectedItem(i))) {
            items.add(new juce::ValueTree(vti->getState()));
        }
    }

    return items;
}

inline void moveItems(juce::TreeView& treeView, juce::OwnedArray<juce::ValueTree> const& items,
                      juce::ValueTree newParent, int insertIndex, juce::UndoManager& undoManager)
{
    if (items.isEmpty()) { return; }

    auto oldOpenness = treeView.getOpennessState(false);

    for (auto i = items.size(); --i >= 0;) {
        auto& v        = *items.getUnchecked(i);
        auto oldParent = v.getParent();

        if (not oldParent.isValid()) { continue; }
        if (newParent == v) { continue; }
        if (newParent.isAChildOf(v)) { continue; }

        if (oldParent == newParent && newParent.indexOf(v) < insertIndex) { --insertIndex; }

        oldParent.removeChild(v, &undoManager);
        newParent.addChild(v, insertIndex, &undoManager);
    }

    if (oldOpenness != nullptr) { treeView.restoreOpennessState(*oldOpenness, false); }
}

} // namespace mc
