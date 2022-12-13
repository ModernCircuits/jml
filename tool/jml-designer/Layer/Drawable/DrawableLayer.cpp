#include "DrawableLayer.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto DrawableLayer::paint(juce::Graphics& g) -> void
{
    g.setColour(getBackground());
    g.fillRect(getBounds());
}

} // namespace mc
