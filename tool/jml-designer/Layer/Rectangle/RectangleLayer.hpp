#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct RectangleLayerIDs
{
    inline static constexpr auto const* type = "Rectangle";
};

struct RectangleLayer final : Layer
{
    using IDs = RectangleLayerIDs;

    RectangleLayer(juce::ValueTree vt, juce::UndoManager& um);
    ~RectangleLayer() override = default;

    [[nodiscard]] auto makeCanvas() -> UniquePtr<LayerCanvas>;
};

} // namespace mc
