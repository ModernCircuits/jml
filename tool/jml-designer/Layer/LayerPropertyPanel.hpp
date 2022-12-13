#pragma once

#include "Layer/Group/GroupLayerTreeViewItem.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct LayerPropertyPanel final
    : juce::Component
    , juce::ChangeListener
{
    explicit LayerPropertyPanel(juce::ChangeBroadcaster& src);
    ~LayerPropertyPanel() override;

    auto resized() -> void override;
    auto changeListenerCallback(juce::ChangeBroadcaster* source) -> void override;

private:
    juce::ChangeBroadcaster& _src;
    juce::PropertyPanel _panel;
};

} // namespace mc
