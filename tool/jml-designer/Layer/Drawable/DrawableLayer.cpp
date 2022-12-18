#include "DrawableLayer.hpp"

#include "Component/PropertyPanel.hpp"

namespace mc {

DrawableLayer::DrawableLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto DrawableLayer::paintLayer(juce::Graphics& g) -> void { g.fillAll(getBackground()); }

auto DrawableLayer::addLayerProperties(juce::PropertyPanel& panel) -> void
{
    auto const fill = juce::Array<juce::PropertyComponent*>{
        makeColorProperty(valueTree(), IDs::background, "Background", true),
        makeSliderProperty(valueTree(), IDs::opacity, "Opacity", 0.0, 1.0, 0.01),
    };

    panel.addSection("Fill", fill);
}
} // namespace mc
