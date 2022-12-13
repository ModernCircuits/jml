#include "DocumentEditor.hpp"

namespace mc {
DocumentEditor::DocumentEditor(Document& document) : _document{document}
{
    addAndMakeVisible(_toolBar);
    addAndMakeVisible(_layerTree);
    addAndMakeVisible(_canvas);
    addAndMakeVisible(_propertyPanel);
}

auto DocumentEditor::resized() -> void
{
    auto area       = getLocalBounds();
    auto panelWidth = area.proportionOfWidth(0.18);
    _toolBar.setBounds(area.removeFromLeft(area.proportionOfWidth(0.03)));
    _layerTree.setBounds(area.removeFromLeft(panelWidth / 2));
    _propertyPanel.setBounds(area.removeFromRight(panelWidth));
    _canvas.setBounds(area);
}
} // namespace mc
