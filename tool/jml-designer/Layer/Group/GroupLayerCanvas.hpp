#pragma once

#include "Layer/Group/GroupLayer.hpp"
#include "Layer/LayerCanvas.hpp"

namespace mc {
struct GroupLayerCanvas final
    : LayerCanvas
    , Layer::Listener
{
    explicit GroupLayerCanvas(GroupLayer& layer);
    ~GroupLayerCanvas() override;

    auto resized() -> void override;
    auto layerPropertyChanged(Layer& layer) -> void override;

private:
    auto addLayer(Layer* layer) -> void;
    auto removeLayer(Layer* layer) -> void;
    auto updateOrder() -> void;

    Vector<UniquePtr<LayerCanvas>> _layers;
};

} // namespace mc
