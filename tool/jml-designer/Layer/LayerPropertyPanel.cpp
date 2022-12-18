#include "LayerPropertyPanel.hpp"

#include "Layer/LayerTree.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

LayerPropertyPanel::LayerPropertyPanel(juce::ChangeBroadcaster& src) : _src{src}
{
    addAndMakeVisible(_panel);
    _src.addChangeListener(this);
}

LayerPropertyPanel::~LayerPropertyPanel() { _src.removeChangeListener(this); }

auto LayerPropertyPanel::resized() -> void { _panel.setBounds(getLocalBounds()); }

auto LayerPropertyPanel::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    _panel.clear();

    auto* const tree = dynamic_cast<LayerTree*>(source);
    if (tree == nullptr) { return; }

    auto* const selected      = tree->getSelectedItem(0);
    auto* const layerTreeItem = dynamic_cast<LayerTreeItem*>(selected);
    if (layerTreeItem == nullptr) { return; }

    layerTreeItem->getLayer().fillPropertyPanel(_panel);
}

} // namespace mc
