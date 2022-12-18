#include "LayerSelection.hpp"

namespace mc {
auto LayerSelection::getLayers() const -> Span<juce::WeakReference<Layer> const> { return _layers; }

auto LayerSelection::clear() -> void
{
    for (auto layer : _layers) {
        if (layer != nullptr) { remove(layer.get()); }
    }
    _layers.clear();
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::add(Layer* layer) -> void
{
    jassert(layer != nullptr);
    jassert(not isSelected(layer));

    _layers.emplace_back(layer);
    layer->setSelected(true);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::remove(Layer* layer) -> void
{
    jassert(layer != nullptr);
    jassert(isSelected(layer));

    std::erase(_layers, layer);
    layer->setSelected(false);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::addOrRemove(Layer* layer) -> void
{
    jassert(layer != nullptr);
    if (not isSelected(layer)) {
        add(layer);
    } else {
        remove(layer);
    }
}

auto LayerSelection::isSelected(Layer* layer) const -> bool
{
    return not ranges::none_of(_layers, [layer](auto const& l) { return l.get() == layer; });
}

auto LayerSelection::addListener(Listener* listener) -> void { _listeners.add(listener); }

auto LayerSelection::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

} // namespace mc
