#include "GroupLayerTreeItem.hpp"

namespace mc {

GroupLayerTreeItem::GroupLayerTreeItem(juce::ValueTree const& v, juce::UndoManager& um) : LayerTreeItem(v, um)
{
    jassert(state.hasType(GroupLayer::IDs::type));
}

auto GroupLayerTreeItem::isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/)
    -> bool
{
    return true;
}

auto GroupLayerTreeItem::itemDropped(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/, int index) -> void
{
    auto& treeView      = *getOwnerView();
    auto selectedLayers = getSelectedTreeViewItems<LayerTreeItem>(treeView);
    moveItems(treeView, selectedLayers, state, index, *getUndoManager());
}

} // namespace mc
