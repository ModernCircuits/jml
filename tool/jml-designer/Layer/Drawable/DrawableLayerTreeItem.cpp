#include "DrawableLayerTreeItem.hpp"

namespace mc {
DrawableLayerTreeItem::DrawableLayerTreeItem(juce::ValueTree const& v, juce::UndoManager& um) : LayerTreeItem(v, um)
{
    jassert(state.hasType(DrawableLayer::IDs::type));
}
} // namespace mc
