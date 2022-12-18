#include "LayerTreeItem.hpp"

#include "Layer/Drawable/DrawableLayerTreeItem.hpp"
#include "Layer/Group/GroupLayerTreeItem.hpp"

namespace mc {

static auto createLayerTreeItemForType(Layer& layer) -> LayerTreeItem*
{
    auto const& v = layer.valueTree();
    if (v.hasType(GroupLayer::IDs::type)) { return new GroupLayerTreeItem{layer}; }
    if (v.hasType(DrawableLayer::IDs::type)) { return new DrawableLayerTreeItem{layer}; }
    jassertfalse;
    return nullptr;
}

LayerTreeItem::LayerTreeItem(Layer& layer) : _layer{&layer}
{
    jassert(_layer != nullptr);
    _layer->addListener(this);
}
LayerTreeItem::~LayerTreeItem()
{
    if (_layer == nullptr) { return; }
    _layer->removeListener(this);
}

auto LayerTreeItem::getState() const -> juce::ValueTree
{
    jassert(_layer != nullptr);
    return _layer->valueTree();
}

auto LayerTreeItem::getUndoManager() const -> juce::UndoManager*
{
    jassert(_layer != nullptr);
    return _layer->undoManager();
}

auto LayerTreeItem::getDisplayText() -> juce::String
{
    jassert(_layer != nullptr);
    return _layer->getName();
}

auto LayerTreeItem::getUniqueName() const -> juce::String
{
    jassert(_layer != nullptr);
    return _layer->getUUID();
}

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
    if (_layer == layer) {
        refreshSubItems();
        treeHasChanged();
        setOpen(true);
    }
}

auto LayerTreeItem::refreshSubItems() -> void
{
    jassert(_layer != nullptr);

    clearSubItems();
    DBG(_layer->getName() << ": " << _layer->getNumChildLayers() << ", " << _layer->valueTree().getNumChildren());

    for (auto* child : _layer->getChildLayers()) {
        if (auto* item = createLayerTreeItemForType(*child); item != nullptr) { addSubItem(item); }
    }
}

} // namespace mc
