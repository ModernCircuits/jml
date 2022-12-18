#include "LayerPropertyPanel.hpp"

#include "Export/ImageExporter.hpp"
#include "Layer/LayerTree.hpp"
#include "Layer/LayerTreeItem.hpp"

namespace mc {

LayerPropertyPanel::LayerPropertyPanel(LayerSelection& selection) : _selection{selection}
{
    addAndMakeVisible(_panel);
    addAndMakeVisible(_export);
    _selection.addListener(this);

    _export.onClick = [this] {
        auto const layers = _selection.getLayers();
        if (layers.size() != 1) { return; }

        auto selected = layers[0];
        if (selected == nullptr) { return; }

        auto snapShotFile = juce::File::getCurrentWorkingDirectory().getChildFile("snapshot.png");
        if (snapShotFile.existsAsFile()) { snapShotFile.deleteFile(); }

        auto out = snapShotFile.createOutputStream();
        if (out == nullptr) { return; }

        auto exporter = ImageExporter{};
        auto result   = exporter.exportLayer(*selected, *out);
        if (result.failed()) { DBG(result.getErrorMessage()); }
    };
}

LayerPropertyPanel::~LayerPropertyPanel() { _selection.removeListener(this); }

auto LayerPropertyPanel::resized() -> void
{
    auto area = getLocalBounds();
    _export.setBounds(area.removeFromBottom(area.proportionOfHeight(0.075)).reduced(2));
    _panel.setBounds(area);
}

auto LayerPropertyPanel::layerSelectionChanged(LayerSelection* selection) -> void
{
    jassertquiet(selection == &_selection);
    _panel.clear();

    auto layers = selection->getLayers();
    if (layers.size() != 1) { return; }

    auto selected = layers[0];
    if (selected == nullptr) { return; }
    selected->fillPropertyPanel(_panel);
}

} // namespace mc
