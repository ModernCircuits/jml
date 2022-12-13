#pragma once

#include "Layer/LayerCanvas.hpp"
#include "Layer/Rectangle/RectangleLayer.hpp"

namespace mc {

struct RectangleLayerCanvas final
    : LayerCanvas
    , Layer::Listener
{
    explicit RectangleLayerCanvas(RectangleLayer& layer);
    ~RectangleLayerCanvas() override;

    auto paint(juce::Graphics& g) -> void override;
    auto layerPropertyChanged(Layer& layer) -> void override;
};

} // namespace mc
