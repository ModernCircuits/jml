#include "SelectionTool.hpp"

#include "Document/DocumentCanvas.hpp"
#include "Layer/Layer.hpp"

namespace mc {

SelectionTool::SelectionTool(DocumentCanvas& c) noexcept : Tool{c}
{
    getDocumentCanvas().addMouseListener(this, true);
    getLayerSelection().addListener(this);
}

SelectionTool::~SelectionTool()
{
    getDocumentCanvas().removeMouseListener(this);
    getLayerSelection().removeListener(this);
}

auto SelectionTool::paintTool(juce::Graphics& g) -> void
{
    auto const& selection = getLayerSelection();
    for (auto layer : selection.getLayers()) {
        jassert(layer.get() != nullptr);
        auto const& lc = layer->getCanvas();
        g.setColour(juce::Colours::blue);
        g.drawRect(getDocumentCanvas().getLocalArea(&lc, lc.getLocalBounds()), 2);
    }
}

auto SelectionTool::mouseDown(juce::MouseEvent const& event) -> void
{
    SCOPE_EXIT { getDocumentCanvas().repaint(); };

    getLayerSelection().clear();
    auto layerCanvas = dynamic_cast<Layer::Canvas*>(event.eventComponent);
    if (layerCanvas == nullptr) { return; }
    getLayerSelection().addOrRemove(&layerCanvas->layer());
}

auto SelectionTool::layerSelectionChanged(LayerSelection* selection) -> void
{
    jassertquiet(selection == &getLayerSelection());
    getDocumentCanvas().repaint();
}

auto SelectionTool::getLayerSelection() -> LayerSelection&
{
    return getDocumentCanvas().document().getLayerSelection();
}
auto SelectionTool::getLayerSelection() const -> LayerSelection const&
{
    return getDocumentCanvas().document().getLayerSelection();
}

} // namespace mc
