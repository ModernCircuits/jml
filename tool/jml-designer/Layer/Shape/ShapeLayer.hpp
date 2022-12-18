#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct ShapeLayerIDs : Layer::IDs
{
    inline static constexpr auto const* type = "Shape";
};

struct ShapeLayer final : Layer
{
    using IDs = ShapeLayerIDs;

    ShapeLayer(juce::ValueTree vt, juce::UndoManager& um);
    ~ShapeLayer() override = default;

    auto paintLayer(juce::Graphics& g) -> void override;
    auto addLayerProperties(juce::PropertyPanel& panel) -> void override;
};

} // namespace mc
