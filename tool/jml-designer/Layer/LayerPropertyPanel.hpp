#pragma once

#include "Layer/LayerSelection.hpp"

#include <mc_gui_extra/mc_gui_extra.hpp>

namespace mc {

struct LayerPropertyPanel final
    : juce::Component
    , LayerSelection::Listener
{
    explicit LayerPropertyPanel(LayerSelection& selection);
    ~LayerPropertyPanel() override;

    auto resized() -> void override;
    auto layerSelectionChanged(LayerSelection* selection) -> void override;

private:
    LayerSelection& _selection;
    juce::PropertyPanel _panel;
};

} // namespace mc
