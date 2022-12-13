#include "GroupLayerTreeViewItem.hpp"

namespace mc {

GroupLayerTreeViewItem::GroupLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um)
    : LayerTreeViewItem(v, um)
{
    jassert(state.hasType(GroupLayer::IDs::type));
}

auto GroupLayerTreeViewItem::isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/)
    -> bool
{
    return true;
}

auto GroupLayerTreeViewItem::itemDropped(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/, int index)
    -> void
{
    auto& treeView      = *getOwnerView();
    auto selectedLayers = getSelectedTreeViewItems<LayerTreeViewItem>(treeView);
    moveItems(treeView, selectedLayers, state, index, *getUndoManager());
}

} // namespace mc
