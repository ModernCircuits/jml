#include "SelectionTool.hpp"

#include "Document/DocumentCanvas.hpp"
#include "Layer/Layer.hpp"

namespace mc {

SelectionTool::SelectionTool(DocumentCanvas& c) noexcept : Tool{c}
{
    canvas().addMouseListener(this, true);
    _selectedTree.addListener(this);
}

SelectionTool::~SelectionTool() { canvas().removeMouseListener(this); }

auto SelectionTool::paintTool(juce::Graphics& g) -> void
{
    auto const* l = _layer.get();
    if (l == nullptr) { return; }
    if (not _selectedTree.isValid()) { return; }

    g.setColour(juce::Colours::blue);
    g.drawRect(canvas().getLocalArea(&l->getCanvas(), l->getCanvas().getLocalBounds()), 2);
}

auto SelectionTool::mouseDown(juce::MouseEvent const& event) -> void
{
    SCOPE_EXIT { canvas().repaint(); };

    auto layerCanvas = dynamic_cast<Layer::Canvas*>(event.eventComponent);
    if (layerCanvas == nullptr) {
        _layer        = nullptr;
        _selectedTree = juce::ValueTree{};
        return;
    }

    _layer        = &layerCanvas->layer();
    _selectedTree = _layer == nullptr ? juce::ValueTree{} : _layer->valueTree();
}

auto SelectionTool::valueTreePropertyChanged(juce::ValueTree& /*tree*/, juce::Identifier const& /*property*/) -> void
{
    if (_layer.get() == nullptr) { return; }
    canvas().repaint();
}

} // namespace mc
