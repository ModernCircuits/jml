#pragma once

#include <mc_gui_extra/mc_gui_extra.hpp>

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
