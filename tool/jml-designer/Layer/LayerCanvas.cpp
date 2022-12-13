#include "LayerCanvas.hpp"

namespace mc {

LayerCanvas::LayerCanvas(Layer& layer) : _layer{&layer} {}

auto LayerCanvas::layer() const -> Layer* { return _layer; }

} // namespace mc
