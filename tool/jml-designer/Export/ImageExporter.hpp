#pragma once

#include "Export/Exporter.hpp"

namespace mc {

struct ImageExporter final : Exporter
{
    ImageExporter()           = default;
    ~ImageExporter() override = default;

    [[nodiscard]] auto exportLayer(Layer& layer, juce::OutputStream& out) -> juce::Result override;
};

} // namespace mc
