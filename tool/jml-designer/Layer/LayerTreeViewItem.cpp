#include "LayerTreeViewItem.hpp"

#include <utility>

#include "Layer/Group/GroupLayerTreeViewItem.hpp"
#include "Layer/Drawable/DrawableLayerTreeViewItem.hpp"

namespace mc {

static auto createLayerTreeViewItemForType(juce::ValueTree const& v, juce::UndoManager& um) -> LayerTreeViewItem*
{
    if (v.hasType(GroupLayer::IDs::type)) { return new GroupLayerTreeViewItem(v, um); }
    if (v.hasType(DrawableLayer::IDs::type)) { return new DrawableLayerTreeViewItem(v, um); }
    jassertfalse;
    return nullptr;
}

LayerTreeViewItem::LayerTreeViewItem(juce::ValueTree v, juce::UndoManager& um) : state(std::move(v)), undoManager(um)
{
    state.addListener(this);
}

auto LayerTreeViewItem::getState() const -> juce::ValueTree { return state; }

auto LayerTreeViewItem::getUndoManager() const -> juce::UndoManager* { return &undoManager; }

auto LayerTreeViewItem::getDisplayText() -> juce::String { return state[Layer::IDs::name].toString(); }

auto LayerTreeViewItem::getUniqueName() const -> juce::String
{
    jassert(state.hasProperty(Layer::IDs::uuid));
    return state[Layer::IDs::uuid].toString();
}

auto LayerTreeViewItem::mightContainSubItems() -> bool { return state.getNumChildren() > 0; }

void LayerTreeViewItem::paintItem(juce::Graphics& g, int width, int height)
{
    g.fillAll(isSelected() ? juce::Colours::black : juce::Colours::lightgrey);
    g.setColour(isSelected() ? juce::Colours::white : juce::Colours::black);
    g.setFont(15.0F);
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

auto LayerTreeViewItem::getDragSourceDescription() -> juce::var { return state.getType().toString(); }

void LayerTreeViewItem::valueTreePropertyChanged(juce::ValueTree& /*treeWhosePropertyHasChanged*/,
                                                 juce::Identifier const& /*property*/)
{
    repaintItem();
}
void LayerTreeViewItem::valueTreeChildAdded(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenAdded*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeViewItem::valueTreeChildRemoved(juce::ValueTree& tree, juce::ValueTree& /*childWhichHasBeenRemoved*/,
                                              int /*indexFromWhichChildWasRemoved*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeViewItem::valueTreeChildOrderChanged(juce::ValueTree& tree, int /*oldIndex*/, int /*newIndex*/)
{
    treeChildrenChanged(tree);
}
void LayerTreeViewItem::valueTreeParentChanged(juce::ValueTree& /*treeWhoseParentHasChanged*/) {}

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
