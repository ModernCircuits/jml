#pragma once

#include "Layer/Layer.hpp"

#include <mc_data_structures/mc_data_structures.hpp>

namespace mc {

struct GroupLayer final
    : Layer
    , ValueTreeObjectList<Layer>
{
    struct IDs
    {
        inline static constexpr auto const* type = "Group";
    };

    GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager);
    ~GroupLayer() override;

    auto resized() -> void override;

private:
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    auto createNewObject(juce::ValueTree const& v) -> Layer* override;
    auto deleteObject(Layer* c) -> void override;
    auto newObjectAdded(Layer* layer) -> void override;
    auto objectRemoved(Layer* layer) -> void override;
    auto objectOrderChanged() -> void override;
};

} // namespace mc
