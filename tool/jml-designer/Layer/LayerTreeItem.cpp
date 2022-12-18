#include "LayerTreeItem.hpp"

#include "Component/TreeView.hpp"
#include "Layer/LayerTree.hpp"

namespace mc {

static auto getSelectedValueTrees(juce::TreeView& treeView) -> Vector<juce::ValueTree>
{
    auto items        = Vector<juce::ValueTree>{};
    auto addValueTree = [&items](auto const& i) { items.push_back(i.getState()); };
    forEachSelectedItemWithType<LayerTreeItem>(treeView, addValueTree);
    return items;
}

LayerTreeItem::LayerTreeItem(Layer& layer) : _layer{layer} { _layer.addListener(this); }
LayerTreeItem::~LayerTreeItem() { _layer.removeListener(this); }

auto LayerTreeItem::getLayer() -> Layer& { return _layer; }
auto LayerTreeItem::getState() const -> juce::ValueTree { return _layer.valueTree(); }

auto LayerTreeItem::getUndoManager() const -> juce::UndoManager* { return _layer.undoManager(); }

auto LayerTreeItem::getDisplayText() -> juce::String { return _layer.getName(); }

auto LayerTreeItem::getUniqueName() const -> juce::String { return _layer.getUUID(); }

auto LayerTreeItem::mightContainSubItems() -> bool { return _layer.getNumChildren() > 0; }

auto LayerTreeItem::paintItem(juce::Graphics& g, int width, int height) -> void
{
    g.fillAll(isSelected() ? juce::Colours::black : juce::Colours::lightgrey);
    g.setColour(isSelected() ? juce::Colours::white : juce::Colours::black);
    g.setFont(15.0F);
    g.drawText(getDisplayText(), 4, 0, width - 4, height, juce::Justification::centredLeft, true);
}

auto LayerTreeItem::itemOpennessChanged(bool isNowOpen) -> void
{
    if (isNowOpen && getNumSubItems() == 0) { return refreshSubItems(); }
    clearSubItems();
}

auto LayerTreeItem::itemSelectionChanged(bool isNowSelected) -> void
{
    auto* const ov = getOwnerView();
    if (ov == nullptr) { return; }

    auto* const layerTree = dynamic_cast<LayerTree*>(ov);
    jassert(layerTree != nullptr);
    if (layerTree == nullptr) { return; }

    auto& selection = layerTree->getDocument().getLayerSelection();
    if (isNowSelected) {
        selection.add(&getLayer());
    } else {
        selection.remove(&getLayer());
    }
}

auto LayerTreeItem::getDragSourceDescription() -> juce::var { return getState().getType().toString(); }

auto LayerTreeItem::isInterestedInDragSource(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/) -> bool
{
    return _layer.mightHaveChildren();
}

auto LayerTreeItem::itemDropped(juce::DragAndDropTarget::SourceDetails const& /*sourceDetails*/, int index) -> void
{
    auto& treeView      = *getOwnerView();
    auto selectedLayers = getSelectedValueTrees(treeView);
    auto oldOpenness    = treeView.getOpennessState(false);
    moveItems(selectedLayers, getState(), index, *getUndoManager());
    if (oldOpenness != nullptr) { treeView.restoreOpennessState(*oldOpenness, false); }
}

auto LayerTreeItem::layerPropertyChanged(Layer* layer, juce::Identifier const& /*property*/) -> void
{
    jassert(&_layer == layer);
    repaintItem();
}

auto LayerTreeItem::layerChildrenChanged(Layer* layer) -> void
{
    jassert(&_layer == layer);
    refreshSubItems();
    treeHasChanged();
    setOpen(true);
}

auto LayerTreeItem::refreshSubItems() -> void
{
    clearSubItems();
    for (auto* child : _layer.getChildren()) {
        auto* item = new LayerTreeItem(*child);
        if (item != nullptr) { addSubItem(item); }
    }
}

} // namespace mc
