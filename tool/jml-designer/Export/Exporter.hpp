#pragma once

#include <mc_core/mc_core.hpp>

namespace mc {

struct Layer;

struct Exporter
{
    virtual ~Exporter() = default;

    [[nodiscard]] virtual auto exportLayer(juce::OutputStream& out, Layer& layer) -> juce::Result = 0;
};

} // namespace mc
