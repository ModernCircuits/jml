#include "ImageExporter.hpp"

#include "Layer/Layer.hpp"

#include <mc_graphics/mc_graphics.hpp>

namespace mc {

[[nodiscard]] static auto makeImageFileFormatForExporter(ImageExporter::Format format)
    -> UniquePtr<juce::ImageFileFormat>
{
    if (format == ImageExporter::Format::jpg) { return makeUnique<juce::JPEGImageFormat>(); }
    if (format == ImageExporter::Format::png) { return makeUnique<juce::PNGImageFormat>(); }
    return nullptr;
}

ImageExporter::ImageExporter(Format format) : _format{format} {}

auto ImageExporter::exportLayer(juce::OutputStream& out, Layer& layer, float scale) -> juce::Result
{
    auto& canvas = layer.getCanvas();
    auto image   = canvas.createComponentSnapshot(canvas.getLocalBounds(), true, scale);
    if (not image.isValid()) { return fail("invalid image returned for layer: {}", layer.getName()); }

    auto format = makeImageFileFormatForExporter(_format);
    if (format == nullptr) { return fail("failed to create image format writer"); }
    if (not format->writeImageToStream(image, out)) { return fail("couldn't write image for: {}", layer.getName()); }

    return juce::Result::ok();
}

} // namespace mc

auto juce::VariantConverter<mc::ImageExporter::Format>::toVar(mc::ImageExporter::Format const& format) -> juce::var
{
    if (format == mc::ImageExporter::Format::invalid) { return "invalid"; }
    if (format == mc::ImageExporter::Format::jpg) { return "jpg"; }
    if (format == mc::ImageExporter::Format::png) { return "png"; }

    jassertfalse;
    return {};
}

auto juce::VariantConverter<mc::ImageExporter::Format>::fromVar(juce::var const& v) -> mc::ImageExporter::Format
{
    if (v == "invalid") { return mc::ImageExporter::Format::invalid; }
    if (v == "jpg") { return mc::ImageExporter::Format::jpg; }
    if (v == "png") { return mc::ImageExporter::Format::png; }

    jassertfalse;
    return mc::ImageExporter::Format::invalid;
}
