#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct LayerTreeViewItem
    : juce::TreeViewItem
    , protected juce::ValueTree::Listener
{
    LayerTreeViewItem(juce::ValueTree v, juce::UndoManager& um);
    ~LayerTreeViewItem() override = default;

    virtual auto getDisplayText() -> juce::String;

    [[nodiscard]] auto getState() const -> juce::ValueTree;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    [[nodiscard]] auto getUniqueName() const -> juce::String override;
    auto mightContainSubItems() -> bool override;

    auto paintItem(juce::Graphics& g, int width, int height) -> void override;
    auto itemOpennessChanged(bool isNowOpen) -> void override;
    auto itemSelectionChanged(bool /*isNowSelected*/) -> void override;

    auto getDragSourceDescription() -> juce::var override;

protected:
    juce::ValueTree state;
    juce::UndoManager& undoManager;

    auto valueTreePropertyChanged(juce::ValueTree& /*treeWhosePropertyHasChanged*/,
                                  juce::Identifier const& /*property*/) -> void override;
    auto valueTreeChildAdded(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenAdded*/) -> void override;
    auto valueTreeChildRemoved(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenRemoved*/,
                               int /*indexFromWhichChildWasRemoved*/) -> void override;
    auto valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/) -> void override;
    auto valueTreeParentChanged(juce::ValueTree& /*treeWhoseParentHasChanged*/) -> void override;

    auto treeChildrenChanged(juce::ValueTree const& tree) -> void;

private:
    auto refreshSubItems() -> void;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerTreeViewItem) // NOLINT
};

} // namespace mc
