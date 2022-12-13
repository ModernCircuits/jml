#pragma once

#include "Component/TreeView.hpp"
#include "Layer/LayerTreeViewItem.hpp"
#include "Layer/Drawable/DrawableLayer.hpp"

namespace mc {

struct DrawableLayerTreeViewItem final : LayerTreeViewItem
{
    DrawableLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~DrawableLayerTreeViewItem() override = default;
};

} // namespace mc
