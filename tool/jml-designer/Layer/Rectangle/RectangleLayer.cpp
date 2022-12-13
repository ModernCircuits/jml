#include "RectangleLayer.hpp"
#include "RectangleLayerCanvas.hpp"

namespace mc {

RectangleLayer::RectangleLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto RectangleLayer::makeCanvas() -> UniquePtr<LayerCanvas> { return makeUnique<RectangleLayerCanvas>(*this); }

} // namespace mc
