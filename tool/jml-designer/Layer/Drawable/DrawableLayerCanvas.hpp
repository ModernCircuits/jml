#pragma once

#include "Layer/Drawable/DrawableLayer.hpp"
#include "Layer/LayerCanvas.hpp"

namespace mc {

struct DrawableLayerCanvas final
    : LayerCanvas
    , Layer::Listener
{
    explicit DrawableLayerCanvas(DrawableLayer& layer);
    ~DrawableLayerCanvas() override;

    auto paint(juce::Graphics& g) -> void override;
    auto layerPropertyChanged(Layer& layer) -> void override;
};

} // namespace mc
