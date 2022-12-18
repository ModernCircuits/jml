#include "LayerTreeItem.hpp"

#include "Layer/Drawable/DrawableLayerTreeItem.hpp"
#include "Layer/Group/GroupLayerTreeItem.hpp"

namespace mc {

static auto createLayerTreeItem(Layer& layer) -> LayerTreeItem*
{
    auto const& v = layer.valueTree();
    if (v.hasType(GroupLayer::IDs::type)) { return new GroupLayerTreeItem{layer}; }
    if (v.hasType(DrawableLayer::IDs::type)) { return new DrawableLayerTreeItem{layer}; }
    jassertfalse;
    return nullptr;
}

LayerTreeItem::LayerTreeItem(Layer& layer) : _layer{layer} { _layer.addListener(this); }
LayerTreeItem::~LayerTreeItem() { _layer.removeListener(this); }

auto LayerTreeItem::getState() const -> juce::ValueTree { return _layer.valueTree(); }

auto LayerTreeItem::getUndoManager() const -> juce::UndoManager* { return _layer.undoManager(); }

auto LayerTreeItem::getDisplayText() -> juce::String { return _layer.getName(); }

auto LayerTreeItem::getUniqueName() const -> juce::String { return _layer.getUUID(); }

auto LayerTreeItem::mightContainSubItems() -> bool { return getState().getNumChildren() > 0; }

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

auto LayerTreeItem::itemSelectionChanged(bool /*isNowSelected*/) -> void
{
    auto* const ov = getOwnerView();
    if (ov == nullptr) { return; }

    auto* const cb = dynamic_cast<juce::ChangeBroadcaster*>(ov);
    if (cb == nullptr) { return; }
    cb->sendChangeMessage();
}

auto LayerTreeItem::getDragSourceDescription() -> juce::var { return getState().getType().toString(); }

// auto LayerTreeItem::valueTreePropertyChanged(juce::ValueTree& /*tree*/, juce::Identifier const& /*property*/) -> void
// {
//     repaintItem();
// }

auto LayerTreeItem::layerChildrenChanged(Layer* layer) -> void { treeChildrenChanged(layer); }

auto LayerTreeItem::treeChildrenChanged(Layer* layer) -> void
{
    if (&_layer == layer) {
        refreshSubItems();
        treeHasChanged();
        setOpen(true);
    }
}

auto LayerTreeItem::refreshSubItems() -> void
{
    clearSubItems();
    for (auto* child : _layer.getChildLayers()) {
        auto* item = createLayerTreeItem(*child);
        if (item != nullptr) { addSubItem(item); }
    }
}

} // namespace mc
