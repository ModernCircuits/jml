#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct LayerTreeItem final
    : juce::TreeViewItem
    , Layer::Listener
{
    explicit LayerTreeItem(Layer& layer);
    ~LayerTreeItem() override;

    [[nodiscard]] auto getDisplayText() -> juce::String;
    [[nodiscard]] auto getState() const -> juce::ValueTree;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    // juce::TreeViewItem
    [[nodiscard]] auto getUniqueName() const -> juce::String override;
    [[nodiscard]] auto mightContainSubItems() -> bool override;

    auto paintItem(juce::Graphics& g, int width, int height) -> void override;
    auto itemOpennessChanged(bool isNowOpen) -> void override;
    auto itemSelectionChanged(bool isNowSelected) -> void override;

    auto getDragSourceDescription() -> juce::var override;
    auto isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& sourceDetails) -> bool override;
    auto itemDropped(juce::DragAndDropTarget::SourceDetails const& sourceDetails, int index) -> void override;

    // Layer::Listener
    auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void override;
    auto layerChildrenChanged(Layer* layer) -> void override;

private:
    auto refreshSubItems() -> void;

    Layer& _layer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LayerTreeItem) // NOLINT
};

} // namespace mc
