#include "DrawableLayer.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um}
{
    valueTree().addListener(this);
}

DrawableLayer::~DrawableLayer() { valueTree().removeListener(this); }

auto DrawableLayer::paint(juce::Graphics& g) -> void
{
    g.setColour(getBackground());
    g.fillRect(getBounds());
}

auto DrawableLayer::valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& /*property*/) -> void
{
    if (tree != valueTree()) { return; }
    getCanvas().repaint();
}

} // namespace mc
