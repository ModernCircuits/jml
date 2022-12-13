#include "SelectionTool.hpp"

#include "Document/DocumentCanvas.hpp"
#include "Layer/LayerCanvas.hpp"

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
    g.drawRect(juce::Rectangle{l->x(), l->y(), l->width(), l->height()}, 2.0F);
}

auto SelectionTool::mouseDown(juce::MouseEvent const& event) -> void
{
    _layer        = dynamic_cast<LayerCanvas*>(event.eventComponent)->layer();
    _selectedTree = _layer == nullptr ? juce::ValueTree{} : _layer->valueTree();
    canvas().repaint();
}

auto SelectionTool::valueTreePropertyChanged(juce::ValueTree& /*tree*/, juce::Identifier const& /*property*/) -> void
{
    if (_layer.get() == nullptr) { return; }
    canvas().repaint();
}

} // namespace mc
