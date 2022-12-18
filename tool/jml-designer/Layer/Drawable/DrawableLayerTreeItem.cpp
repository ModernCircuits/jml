#include "DrawableLayerTreeItem.hpp"

namespace mc {
DrawableLayerTreeItem::DrawableLayerTreeItem(Layer& layer) : LayerTreeItem{layer}
{
    jassert(getState().hasType(DrawableLayer::IDs::type));
}
} // namespace mc
