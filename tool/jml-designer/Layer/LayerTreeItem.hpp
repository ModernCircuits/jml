#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct LayerTreeItem
    : juce::TreeViewItem
    , protected Layer::Listener
{
    explicit LayerTreeItem(Layer& layer);
    ~LayerTreeItem() override;

    virtual auto getDisplayText() -> juce::String;

    [[nodiscard]] auto getState() const -> juce::ValueTree;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    [[nodiscard]] auto getUniqueName() const -> juce::String override;
    auto mightContainSubItems() -> bool override;

    auto paintItem(juce::Graphics& g, int width, int height) -> void override;
    auto itemOpennessChanged(bool isNowOpen) -> void override;
    auto itemSelectionChanged(bool isNowSelected) -> void override;

    auto getDragSourceDescription() -> juce::var override;

protected:
    Layer& _layer;

    auto layerChildrenChanged(Layer* layer) -> void override;
    auto treeChildrenChanged(Layer* layer) -> void;

private:
    auto refreshSubItems() -> void;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerTreeItem) // NOLINT
};

} // namespace mc
