#pragma once

#include "Component/TreeView.hpp"
#include "Layer/Drawable/DrawableLayer.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

struct DrawableLayerTreeItem final : LayerTreeItem
{
    DrawableLayerTreeItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~DrawableLayerTreeItem() override = default;
};

} // namespace mc
