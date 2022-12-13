#pragma once

#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct Layer;

struct LayerCanvas : juce::Component
{
    explicit LayerCanvas(Layer& layer);
    ~LayerCanvas() override = default;

    [[nodiscard]] auto layer() const -> Layer*;

private:
    Layer* _layer;
};

} // namespace mc
