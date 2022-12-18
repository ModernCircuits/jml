#include "LayerPropertyPanel.hpp"

#include "Layer/LayerTree.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

LayerPropertyPanel::LayerPropertyPanel(LayerSelection& selection) : _selection{selection}
{
    addAndMakeVisible(_panel);
    _selection.addListener(this);
}

LayerPropertyPanel::~LayerPropertyPanel() { _selection.removeListener(this); }

auto LayerPropertyPanel::resized() -> void { _panel.setBounds(getLocalBounds()); }

auto LayerPropertyPanel::layerSelectionChanged(LayerSelection* selection) -> void
{
    jassertquiet(selection == &_selection);
    _panel.clear();

    auto layers = selection->getLayers();
    DBG("SELECTED: " << layers.size());
    for (auto l : layers) { DBG("\t" << l->getName()); }

    if (layers.size() != 1) { return; }
    layers[0]->fillPropertyPanel(_panel);
}

} // namespace mc
