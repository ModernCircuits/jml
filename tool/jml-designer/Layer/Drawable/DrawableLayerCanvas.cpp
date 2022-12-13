#include "DrawableLayerCanvas.hpp"

namespace mc {

DrawableLayerCanvas::DrawableLayerCanvas(DrawableLayer& l) : LayerCanvas{l} { layer()->addListener(this); }

DrawableLayerCanvas::~DrawableLayerCanvas() { layer()->removeListener(this); }

auto DrawableLayerCanvas::paint(juce::Graphics& g) -> void
{
    g.setColour(layer()->getBackground());
    g.fillRect(getLocalBounds());
}

auto DrawableLayerCanvas::layerPropertyChanged(Layer& /*layer*/) -> void { repaint(); }

} // namespace mc
