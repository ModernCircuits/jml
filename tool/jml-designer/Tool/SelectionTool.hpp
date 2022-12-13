#pragma once

#include "Tool/Tool.hpp"

namespace mc {

struct Layer;

struct SelectionTool final
    : Tool
    , juce::MouseListener
    , juce::ValueTree::Listener
{
    explicit SelectionTool(DocumentCanvas& canvas) noexcept;
    ~SelectionTool() override;

    auto paintTool(juce::Graphics& g) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;
    auto valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void override;

private:
    juce::WeakReference<Layer> _layer{nullptr};
    juce::ValueTree _selectedTree{};
};

} // namespace mc
