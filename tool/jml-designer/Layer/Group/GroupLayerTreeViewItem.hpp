#pragma once

#include "Component/TreeView.hpp"
#include "Layer/Group/GroupLayer.hpp"
#include "Layer/LayerTreeViewItem.hpp"

namespace mc {

struct GroupLayerTreeViewItem final : LayerTreeViewItem
{
    GroupLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~GroupLayerTreeViewItem() override = default;

    auto isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& sourceDetails) -> bool override;
    auto itemDropped(juce::DragAndDropTarget::SourceDetails const& sourceDetails, int index) -> void override;
};

} // namespace mc
