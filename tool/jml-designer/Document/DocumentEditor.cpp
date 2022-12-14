#include "DocumentEditor.hpp"

namespace mc {
DocumentEditor::DocumentEditor(Document& document) : _document{document}
{
    _componentTree.setRootComponent(&document.rootLayer()->getCanvas());
    addAndMakeVisible(_toolBar);
    addAndMakeVisible(_layerTree);
    addAndMakeVisible(_canvas);
    addAndMakeVisible(_propertyPanel);
    addAndMakeVisible(_componentTree);
}

auto DocumentEditor::resized() -> void
{
    auto area       = getLocalBounds();
    auto panelWidth = area.proportionOfWidth(0.18);
    _toolBar.setBounds(area.removeFromLeft(area.proportionOfWidth(0.03)));
    _layerTree.setBounds(area.removeFromLeft(panelWidth / 2));

    auto panels = area.removeFromRight(panelWidth);
    _propertyPanel.setBounds(panels.removeFromTop(panels.proportionOfHeight(0.70)));
    _componentTree.setBounds(panels);

    _canvas.setBounds(area);
}
} // namespace mc
