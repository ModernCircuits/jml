#include "LayerSelection.hpp"

namespace mc {
auto LayerSelection::getLayers() const -> Span<juce::WeakReference<Layer> const> { return _layers; }

auto LayerSelection::clear() -> void
{
    _layers.clear();
    for (auto l : _layers) { l->setSelected(false); }
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::add(Layer* layer) -> void
{
    jassert(ranges::none_of(_layers, [layer](auto const& l) { return l.get() == layer; }));

    _layers.emplace_back(layer);
    layer->setSelected(true);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::remove(Layer* layer) -> void
{
    jassert(not ranges::none_of(_layers, [layer](auto const& l) { return l.get() == layer; }));

    layer->setSelected(false);
    std::erase(_layers, layer);
    _listeners.call(&Listener::layerSelectionChanged, this);
}

auto LayerSelection::addOrRemove(Layer* layer) -> void
{
    if (ranges::none_of(_layers, [layer](auto const& l) { return l.get() == layer; })) {
        add(layer);
    } else {
        remove(layer);
    }
}

auto LayerSelection::addListener(Listener* listener) -> void { _listeners.add(listener); }

auto LayerSelection::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

} // namespace mc
