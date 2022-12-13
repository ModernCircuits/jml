#include "DrawableLayer.hpp"
#include "DrawableLayerCanvas.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto DrawableLayer::makeCanvas() -> UniquePtr<LayerCanvas> { return makeUnique<DrawableLayerCanvas>(*this); }

} // namespace mc
