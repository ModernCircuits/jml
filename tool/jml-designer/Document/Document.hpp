#pragma once

#include "Layer/Layer.hpp"
#include "Layer/LayerSelection.hpp"

#include <mc_data_structures/mc_data_structures.hpp>

namespace mc {

struct Document
{
    Document(juce::ValueTree valueTree, juce::UndoManager* um);

    [[nodiscard]] auto getRootLayer() const -> Layer*;
    [[nodiscard]] auto getLayerSelection() -> LayerSelection&;
    [[nodiscard]] auto getLayerSelection() const -> LayerSelection const&;

    [[nodiscard]] auto getValueTree() -> juce::ValueTree&;
    [[nodiscard]] auto getValueTree() const -> juce::ValueTree const&;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    auto save(juce::File const& file) -> void;
    [[nodiscard]] static auto load(juce::File const& file, juce::UndoManager* um) -> UniquePtr<Document>;

private:
    juce::ValueTree _valueTree;
    juce::UndoManager* _undoManager;

    UniquePtr<Layer> _root;
    LayerSelection _layerSelection;
};

} // namespace mc
