#include "DrawableLayer.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um}
{
    valueTree().addListener(this);
}

DrawableLayer::~DrawableLayer() { valueTree().removeListener(this); }

auto DrawableLayer::paintLayer(juce::Graphics& g) -> void
{
    g.setColour(getBackground());
    g.fillRect(getBounds());
}

} // namespace mc
