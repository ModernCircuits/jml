#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct DrawableLayerIDs : Layer::IDs
{
    inline static constexpr auto const* type = "Drawable";
};

struct DrawableLayer final : Layer
{
    using IDs = DrawableLayerIDs;

    DrawableLayer(juce::ValueTree vt, juce::UndoManager& um);
    ~DrawableLayer() override = default;

    auto paintLayer(juce::Graphics& g) -> void override;
    auto addLayerProperties(juce::PropertyPanel& panel) -> void override;
};

} // namespace mc
