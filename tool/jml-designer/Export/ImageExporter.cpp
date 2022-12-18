#include "ImageExporter.hpp"

#include "Layer/Layer.hpp"

#include <mc_graphics/mc_graphics.hpp>

namespace mc {

auto ImageExporter::exportLayer(Layer& layer, juce::OutputStream& out) -> juce::Result
{
    auto& canvas  = layer.getCanvas();
    auto snapshot = canvas.createComponentSnapshot(canvas.getBounds());
    if (not snapshot.isValid()) { return fail("invalid image returned for layer: {}", layer.getName()); }

    auto png = juce::PNGImageFormat{};
    if (not png.writeImageToStream(snapshot, out)) {
        return fail("could not write png snapshot for layer: {}", layer.getName());
    }

    return juce::Result::ok();
}

} // namespace mc
