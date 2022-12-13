#include "DrawableLayerTreeViewItem.hpp"

namespace mc {
DrawableLayerTreeViewItem::DrawableLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um)
    : LayerTreeViewItem(v, um)
{
    jassert(state.hasType(DrawableLayer::IDs::type));
}
} // namespace mc
