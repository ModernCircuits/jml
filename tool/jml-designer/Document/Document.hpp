#pragma once

#include "Layer/Layer.hpp"

#include <mc_data_structures/mc_data_structures.hpp>

namespace mc {

struct GroupLayer;

struct Document
{
    Document(juce::ValueTree valueTree, juce::UndoManager* um);

    [[nodiscard]] auto rootLayer() const -> Layer*;

    [[nodiscard]] auto valueTree() -> juce::ValueTree&;
    [[nodiscard]] auto valueTree() const -> juce::ValueTree const&;
    [[nodiscard]] auto undoManager() const -> juce::UndoManager*;

    auto save(juce::File const& file) -> void;
    [[nodiscard]] static auto load(juce::File const& file, juce::UndoManager* um) -> UniquePtr<Document>;

private:
    juce::ValueTree _valueTree;
    juce::UndoManager* _undoManager;

    UniquePtr<GroupLayer> _root;
};

} // namespace mc
