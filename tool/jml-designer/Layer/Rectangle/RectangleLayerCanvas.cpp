#include "RectangleLayerCanvas.hpp"

namespace mc {

RectangleLayerCanvas::RectangleLayerCanvas(RectangleLayer& l) : LayerCanvas{l} { layer()->addListener(this); }

RectangleLayerCanvas::~RectangleLayerCanvas() { layer()->removeListener(this); }

auto RectangleLayerCanvas::paint(juce::Graphics& g) -> void
{
    g.setColour(layer()->background());
    g.fillRect(getLocalBounds());
}

auto RectangleLayerCanvas::layerPropertyChanged(Layer& /*layer*/) -> void { repaint(); }

} // namespace mc
