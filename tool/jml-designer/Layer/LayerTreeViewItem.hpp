#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct LayerTreeViewItem
    : juce::TreeViewItem
    , protected juce::ValueTree::Listener
{
    LayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~LayerTreeViewItem() override = default;

    virtual auto getDisplayText() -> juce::String;

    auto getState() const -> juce::ValueTree;
    auto getUndoManager() const -> juce::UndoManager*;

    auto getUniqueName() const -> juce::String override;
    auto mightContainSubItems() -> bool override;

    auto paintItem(juce::Graphics& g, int width, int height) -> void override;
    auto itemOpennessChanged(bool isNowOpen) -> void override;
    auto itemSelectionChanged(bool /*isNowSelected*/) -> void override;

    auto getDragSourceDescription() -> juce::var override;

protected:
    juce::ValueTree state;
    juce::UndoManager& undoManager;

    auto valueTreePropertyChanged(juce::ValueTree&, juce::Identifier const&) -> void override;
    auto valueTreeChildAdded(juce::ValueTree& tree, juce::ValueTree&) -> void override;
    auto valueTreeChildRemoved(juce::ValueTree& tree, juce::ValueTree&, int) -> void override;
    auto valueTreeChildOrderChanged(juce::ValueTree& tree, int, int) -> void override;
    auto valueTreeParentChanged(juce::ValueTree&) -> void override;

    auto treeChildrenChanged(juce::ValueTree const& tree) -> void;

private:
    auto refreshSubItems() -> void;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerTreeViewItem)
};

} // namespace mc
