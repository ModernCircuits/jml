#include "Layer.hpp"

#include "Layer/Layer.hpp"

namespace mc {

LayerCanvas::LayerCanvas(Layer& layer) : _layer{layer}
{
    _layer.addListener(this);
    setComponentID(layer.getUUID());
}

LayerCanvas::~LayerCanvas() { _layer.removeListener(this); }

auto LayerCanvas::layer() -> Layer& { return _layer; }
auto LayerCanvas::layer() const -> Layer const& { return _layer; }

auto LayerCanvas::paint(juce::Graphics& g) -> void
{
    g.fillAll(_layer.getBackgroundFill());
    _layer.paintLayer(g);
}

auto LayerCanvas::paintOverChildren(juce::Graphics& g) -> void { g.fillAll(_layer.getOverlayFill()); }

auto LayerCanvas::layerPropertyChanged(Layer* l, juce::Identifier const& property) -> void
{
    if (l->valueTree() != layer().valueTree()) { return repaint(); }

    // ID & Name
    using IDs = Layer::IDs;
    if (property == juce::StringRef{IDs::uuid}) { setComponentID(layer().getUUID()); }
    if (property == juce::StringRef{IDs::name}) { setName(layer().getName()); }

    // Size
    auto const hasID   = [&](auto id) { return property == juce::StringRef{id}; };
    auto const sizeIDs = Array<char const*, 4>{IDs::x, IDs::y, IDs::width, IDs::height};
    if (ranges::any_of(sizeIDs, hasID)) { setBounds(layer().getBounds().toNearestInt()); }

    repaint();
}
} // namespace mc
