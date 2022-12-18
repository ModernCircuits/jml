#include "DrawableLayer.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto DrawableLayer::paintLayer(juce::Graphics& g) -> void { g.fillAll(getBackground()); }

} // namespace mc
