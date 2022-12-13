#pragma once

#include "Component/TreeView.hpp"
#include "Layer/LayerTreeViewItem.hpp"
#include "Layer/Rectangle/RectangleLayer.hpp"

namespace mc {

struct RectangleLayerTreeViewItem final : LayerTreeViewItem
{
    RectangleLayerTreeViewItem(juce::ValueTree const& v, juce::UndoManager& um);
    ~RectangleLayerTreeViewItem() override = default;
};

} // namespace mc
