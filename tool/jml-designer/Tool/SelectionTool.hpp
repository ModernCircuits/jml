#pragma once

#include "Layer/LayerSelection.hpp"
#include "Tool/Tool.hpp"

namespace mc {

struct Layer;

struct SelectionTool final
    : Tool
    , LayerSelection::Listener
    , juce::MouseListener
{
    explicit SelectionTool(DocumentCanvas& canvas) noexcept;
    ~SelectionTool() override;

    auto paintTool(juce::Graphics& g) -> void override;
    auto layerSelectionChanged(LayerSelection* selection) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;

private:
    auto getLayerSelection() -> LayerSelection&;
    [[nodiscard]] auto getLayerSelection() const -> LayerSelection const&;
};

} // namespace mc
