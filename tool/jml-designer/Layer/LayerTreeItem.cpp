#include "LayerTreeItem.hpp"

#include "Layer/Drawable/DrawableLayerTreeItem.hpp"
#include "Layer/Group/GroupLayerTreeItem.hpp"

namespace mc {

static auto createLayerTreeItemForType(juce::ValueTree const& v, juce::UndoManager& um) -> LayerTreeItem*
{
    if (v.hasType(GroupLayer::IDs::type)) { return new GroupLayerTreeItem(v, um); }
    if (v.hasType(DrawableLayer::IDs::type)) { return new DrawableLayerTreeItem(v, um); }
    jassertfalse;
    return nullptr;
}

LayerTreeItem::LayerTreeItem(juce::ValueTree v, juce::UndoManager& um) : state(std::move(v)), undoManager(um)
{
    state.addListener(this);
}

auto LayerTreeItem::getState() const -> juce::ValueTree { return state; }

auto LayerTreeItem::getUndoManager() const -> juce::UndoManager* { return &undoManager; }

auto LayerTreeItem::getDisplayText() -> juce::String { return state[Layer::IDs::name].toString(); }

auto LayerTreeItem::getUniqueName() const -> juce::String
{
    jassert(state.hasProperty(Layer::IDs::uuid));
    return state[Layer::IDs::uuid].toString();
}

auto LayerTreeItem::mightContainSubItems() -> bool { return state.getNumChildren() > 0; }

void LayerTreeItem::paintItem(juce::Graphics& g, int width, int height)
{
    g.fillAll(isSelected() ? juce::Colours::black : juce::Colours::lightgrey);
    g.setColour(isSelected() ? juce::Colours::white : juce::Colours::black);
    g.setFont(15.0F);
    g.drawText(getDisplayText(), 4, 0, width - 4, height, juce::Justification::centredLeft, true);
}

void LayerTreeItem::itemOpennessChanged(bool isNowOpen)
{
    if (isNowOpen && getNumSubItems() == 0) {
        refreshSubItems();
    } else {
        clearSubItems();
    }
}

void LayerTreeItem::itemSelectionChanged(bool /*isNowSelected*/)
{
    auto* const ov = getOwnerView();
    if (ov == nullptr) { return; }

    auto* const cb = dynamic_cast<juce::ChangeBroadcaster*>(ov);
    if (cb == nullptr) { return; }
    cb->sendChangeMessage();
}

auto LayerTreeItem::getDragSourceDescription() -> juce::var { return state.getType().toString(); }

void LayerTreeItem::valueTreePropertyChanged(juce::ValueTree& /*treeWhosePropertyHasChanged*/,
                                             juce::Identifier const& /*property*/)
{
    repaintItem();
}
void LayerTreeItem::valueTreeChildAdded(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenAdded*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeItem::valueTreeChildRemoved(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenRemoved*/,
                                          int /*indexFromWhichChildWasRemoved*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeItem::valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeItem::valueTreeParentChanged(juce::ValueTree& /*treeWhoseParentHasChanged*/) {}

void LayerTreeItem::treeChildrenChanged(juce::ValueTree const& tree)
{
    if (tree == state) {
        refreshSubItems();
        treeHasChanged();
        setOpen(true);
    }
}

void LayerTreeItem::refreshSubItems()
{
    clearSubItems();

    for (auto const& v : state) {
        if (auto* item = createLayerTreeItemForType(v, undoManager); item != nullptr) { addSubItem(item); }
    }
}

} // namespace mc
