#include "LayerListener.hpp"

#include "Layer/Layer.hpp"

namespace mc {

auto LayerListener::layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void
{
    juce::ignoreUnused(layer, property);
}
auto LayerListener::layerChildrenChanged(Layer* layer) -> void { juce::ignoreUnused(layer); }

auto LayerListener::layerSelectionChanged(Layer* layer) -> void { juce::ignoreUnused(layer); }

auto LayerListener::layerBeingDeleted(Layer* layer) -> void { juce::ignoreUnused(layer); }

} // namespace mc
