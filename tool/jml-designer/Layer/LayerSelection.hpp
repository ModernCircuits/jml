#pragma once

#include "Layer/Layer.hpp"

namespace mc {
struct LayerSelection;

struct LayerSelectionListener
{
    virtual ~LayerSelectionListener() = default;

    virtual auto layerSelectionChanged(LayerSelection* selection) -> void = 0;
};

struct LayerSelection
{
    using Listener = LayerSelectionListener;

    LayerSelection() = default;

    [[nodiscard]] auto getLayers() const -> Span<juce::WeakReference<Layer> const>;

    auto add(Layer* layer) -> void;
    auto remove(Layer* layer) -> void;
    auto addOrRemove(Layer* layer) -> void;
    auto clear() -> void;

    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

private:
    juce::ListenerList<Listener> _listeners;
    Vector<juce::WeakReference<Layer>> _layers{};
};

} // namespace mc
