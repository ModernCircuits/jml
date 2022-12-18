#pragma once

#include "Component/TreeView.hpp"
#include "Layer/Drawable/DrawableLayer.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

struct DrawableLayerTreeItem final : LayerTreeItem
{
    explicit DrawableLayerTreeItem(Layer& layer);
    ~DrawableLayerTreeItem() override = default;
};

} // namespace mc
