#pragma once

#include <mc_core/mc_core.hpp>

namespace mc {

struct Layer;

struct Exporter
{
    virtual ~Exporter() = default;

    [[nodiscard]] virtual auto exportLayer(Layer& layer, juce::OutputStream& out) -> juce::Result = 0;
};

} // namespace mc
