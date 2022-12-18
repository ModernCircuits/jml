#include "LayerSelection.hpp"

namespace mc {
auto LayerSelection::getLayers() const -> Span<juce::WeakReference<Layer> const> { return _layers; }

auto LayerSelection::clear() -> void
{
    _layers.clear();
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::add(Layer* layer) -> void
{
    _layers.emplace_back(layer);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::remove(Layer* layer) -> void
{
    std::erase(_layers, layer);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::addListener(Listener* listener) -> void { _listeners.add(listener); }

auto LayerSelection::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

} // namespace mc
