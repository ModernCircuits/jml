#include "GroupLayerTreeItem.hpp"

namespace mc {

static auto getSelectedValueTrees(juce::TreeView& treeView) -> Vector<juce::ValueTree>
{
    auto items        = Vector<juce::ValueTree>{};
    auto addValueTree = [&items](auto const& i) { items.push_back(i.getState()); };
    forEachSelectedItemWithType<LayerTreeItem>(treeView, addValueTree);
    return items;
}

GroupLayerTreeItem::GroupLayerTreeItem(Layer& layer) : LayerTreeItem{layer}
{
    jassert(getState().hasType(GroupLayer::IDs::type));
}

auto GroupLayerTreeItem::isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/)
    -> bool
{
    return true;
}

auto GroupLayerTreeItem::itemDropped(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/, int index) -> void
{
    auto& treeView      = *getOwnerView();
    auto selectedLayers = getSelectedValueTrees(treeView);
    auto oldOpenness    = treeView.getOpennessState(false);
    moveItems(selectedLayers, getState(), index, *getUndoManager());
    if (oldOpenness != nullptr) { treeView.restoreOpennessState(*oldOpenness, false); }
}

} // namespace mc
