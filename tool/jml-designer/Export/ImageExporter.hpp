#pragma once

#include "Export/Exporter.hpp"

namespace mc {

struct ImageExporter final : Exporter
{
    enum struct Format
    {
        invalid,
        jpg,
        png,
    };

    explicit ImageExporter(Format format);
    ~ImageExporter() override = default;

    [[nodiscard]] auto exportLayer(juce::OutputStream& out, Layer& layer, float scale) -> juce::Result override;

private:
    Format _format{Format::invalid};
};

} // namespace mc

template<>
struct juce::VariantConverter<mc::ImageExporter::Format>
{
    [[nodiscard]] static auto toVar(mc::ImageExporter::Format const& format) -> juce::var;
    [[nodiscard]] static auto fromVar(juce::var const& v) -> mc::ImageExporter::Format;
};
