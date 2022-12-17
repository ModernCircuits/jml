#pragma once

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

auto forEachSelectedItem(juce::TreeView& treeView, auto callback) -> void
{
    for (auto i{0}; i < treeView.getNumSelectedItems(); ++i) {
        auto* item = treeView.getSelectedItem(i);
        jassert(item != nullptr);
        callback(*item);
    }
}

template<typename Type>
auto forEachSelectedItemWithType(juce::TreeView& treeView, auto callback) -> void
{
    forEachSelectedItem(treeView, [&callback](auto& item) {
        auto* typed = dynamic_cast<Type*>(&item);
        if (typed == nullptr) { return; }
        callback(*typed);
    });
}

inline void moveItems(Span<juce::ValueTree const> items, juce::ValueTree newParent, int insertIndex,
                      juce::UndoManager& undoManager)
{
    if (items.empty()) { return; }

    for (auto i{mc::ssize(items) - 1}; i >= 0; --i) {
        auto const& v  = items[static_cast<size_t>(i)];
        auto oldParent = v.getParent();

        if (not oldParent.isValid()) { continue; }
        if (newParent == v) { continue; }
        if (newParent.isAChildOf(v)) { continue; }

        if (oldParent == newParent && newParent.indexOf(v) < insertIndex) { --insertIndex; }

        oldParent.removeChild(v, &undoManager);
        newParent.addChild(v, insertIndex, &undoManager);
    }
}

} // namespace mc
