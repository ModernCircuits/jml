#include "LayerPropertyPanel.hpp"

#include "Layer/LayerTreeView.hpp"
#include "Property/ColorPropertyComponent.hpp"

namespace mc {

static auto makeTextProperty(auto& vt, auto const& id, auto const& name, bool editable)
{
    return new juce::TextPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, 64, false, editable};
}

static auto makeSliderProperty(auto& vt, auto const& id, auto const& name, double minVal, double maxVal,
                               double interval)
{
    return new juce::SliderPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, minVal, maxVal, interval};
}

static auto makeColorProperty(auto& vt, auto const& id, auto const& name, bool showAlpha)
{
    return new ColorPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, showAlpha};
}

LayerPropertyPanel::LayerPropertyPanel(juce::ChangeBroadcaster& src) : _src{src}
{
    addAndMakeVisible(_panel);
    _src.addChangeListener(this);
}

LayerPropertyPanel::~LayerPropertyPanel() { _src.removeChangeListener(this); }

auto LayerPropertyPanel::resized() -> void { _panel.setBounds(getLocalBounds()); }

auto LayerPropertyPanel::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    auto* const tree = dynamic_cast<LayerTreeView*>(source);
    if (tree == nullptr) { return; }

    auto* const selected = tree->getSelectedItem(0);
    auto* const layer    = dynamic_cast<LayerTreeViewItem*>(selected);
    if (layer == nullptr) { return; }

    auto vt = layer->getState();

    auto const general = juce::Array<juce::PropertyComponent*>{
        makeTextProperty(vt, Layer::IDs::uuid, "UUID", false),
        makeTextProperty(vt, Layer::IDs::name, "Name", true),
    };

    auto const position = juce::Array<juce::PropertyComponent*>{
        makeSliderProperty(vt, Layer::IDs::x, "X", 0.0, 1000.0, 1.0),
        makeSliderProperty(vt, Layer::IDs::y, "Y", 0.0, 1000.0, 1.0),
        makeSliderProperty(vt, Layer::IDs::width, "Width", 0.0, 1000.0, 1.0),
        makeSliderProperty(vt, Layer::IDs::height, "Height", 0.0, 1000.0, 1.0),
    };

    auto const fill = juce::Array<juce::PropertyComponent*>{
        makeColorProperty(vt, Layer::IDs::background, "Background", true),
        makeSliderProperty(vt, Layer::IDs::opacity, "Opacity", 0.0, 1.0, 0.01),
    };

    _panel.clear();
    _panel.addSection("Layer", general);
    _panel.addSection("Position", position);
    _panel.addSection("Fill", fill);
}

} // namespace mc
