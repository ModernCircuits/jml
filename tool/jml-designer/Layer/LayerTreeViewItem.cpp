#include "LayerTreeViewItem.hpp"

#include "Layer/Group/GroupLayerTreeViewItem.hpp"
#include "Layer/Rectangle/RectangleLayerTreeViewItem.hpp"

namespace mc {

static auto createLayerTreeViewItemForType(juce::ValueTree const& v, juce::UndoManager& um) -> LayerTreeViewItem*
{
    if (v.hasType(GroupLayer::IDs::type)) return new GroupLayerTreeViewItem(v, um);
    if (v.hasType(RectangleLayer::IDs::type)) return new RectangleLayerTreeViewItem(v, um);
    jassertfalse;
    return nullptr;
}

LayerTreeViewItem::LayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um) : state(v), undoManager(um)
{
    state.addListener(this);
}

juce::ValueTree LayerTreeViewItem::getState() const { return state; }

juce::UndoManager* LayerTreeViewItem::getUndoManager() const { return &undoManager; }

juce::String LayerTreeViewItem::getDisplayText() { return state[Layer::IDs::name].toString(); }

juce::String LayerTreeViewItem::getUniqueName() const
{
    jassert(state.hasProperty(Layer::IDs::uuid));
    return state[Layer::IDs::uuid].toString();
}

bool LayerTreeViewItem::mightContainSubItems() { return state.getNumChildren() > 0; }

void LayerTreeViewItem::paintItem(juce::Graphics& g, int width, int height)
{
    g.fillAll(isSelected() ? juce::Colours::black : juce::Colours::lightgrey);
    g.setColour(isSelected() ? juce::Colours::white : juce::Colours::black);
    g.setFont(15.0f);
    g.drawText(getDisplayText(), 4, 0, width - 4, height, juce::Justification::centredLeft, true);
}

void LayerTreeViewItem::itemOpennessChanged(bool isNowOpen)
{
    if (isNowOpen && getNumSubItems() == 0) {
        refreshSubItems();
    } else {
        clearSubItems();
    }
}

void LayerTreeViewItem::itemSelectionChanged(bool /*isNowSelected*/)
{
    auto* const ov = getOwnerView();
    if (ov == nullptr) { return; }

    auto* const cb = dynamic_cast<juce::ChangeBroadcaster*>(ov);
    if (cb == nullptr) { return; }
    cb->sendChangeMessage();
}

juce::var LayerTreeViewItem::getDragSourceDescription() { return state.getType().toString(); }

void LayerTreeViewItem::valueTreePropertyChanged(juce::ValueTree&, juce::Identifier const&) { repaintItem(); }
void LayerTreeViewItem::valueTreeChildAdded(juce::ValueTree& tree, juce::ValueTree&) { treeChildrenChanged(tree); }
void LayerTreeViewItem::valueTreeChildRemoved(juce::ValueTree& tree, juce::ValueTree&, int)
{
    treeChildrenChanged(tree);
}
void LayerTreeViewItem::valueTreeChildOrderChanged(juce::ValueTree& tree, int, int) { treeChildrenChanged(tree); }
void LayerTreeViewItem::valueTreeParentChanged(juce::ValueTree&) {}

void LayerTreeViewItem::treeChildrenChanged(juce::ValueTree const& tree)
{
    if (tree == state) {
        refreshSubItems();
        treeHasChanged();
        setOpen(true);
    }
}

void LayerTreeViewItem::refreshSubItems()
{
    clearSubItems();

    for (auto const& v : state) {
        if (auto* item = createLayerTreeViewItemForType(v, undoManager); item != nullptr) { addSubItem(item); }
    }
}

} // namespace mc
