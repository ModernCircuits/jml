#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct DrawableLayerIDs
{
    inline static constexpr auto const* type = "Drawable";
};

struct DrawableLayer final
    : Layer
    , juce::ValueTree::Listener
{
    using IDs = DrawableLayerIDs;

    DrawableLayer(juce::ValueTree vt, juce::UndoManager& um);
    ~DrawableLayer() override;

    auto paintLayer(juce::Graphics& g) -> void override;
};

} // namespace mc
