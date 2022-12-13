#include "RectangleLayerTreeViewItem.hpp"

namespace mc {
RectangleLayerTreeViewItem::RectangleLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um)
    : LayerTreeViewItem(v, um)
{
    jassert(state.hasType(RectangleLayer::IDs::type));
}
} // namespace mc
