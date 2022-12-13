#pragma once

#include "Component/TreeView.hpp"
#include "Layer/Group/GroupLayer.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

struct GroupLayerTreeItem final : LayerTreeItem
{
    GroupLayerTreeItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~GroupLayerTreeItem() override = default;

    auto isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& sourceDetails) -> bool override;
    auto itemDropped(juce::DragAndDropTarget::SourceDetails const& sourceDetails, int index) -> void override;
};

} // namespace mc
