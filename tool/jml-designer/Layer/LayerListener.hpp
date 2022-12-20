#pragma once

#include <mc_gui_extra/mc_gui_extra.hpp>

namespace mc {

struct Layer;

struct LayerListener
{
    virtual ~LayerListener() = default;

    virtual auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void;
    virtual auto layerChildrenChanged(Layer* layer) -> void;
    virtual auto layerSelectionChanged(Layer* layer) -> void;
    virtual auto layerBeingDeleted(Layer* layer) -> void;
};

} // namespace mc
