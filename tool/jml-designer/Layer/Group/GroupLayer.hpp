#pragma once

#include "Layer/Layer.hpp"

#include <mc_data_structures/mc_data_structures.hpp>

namespace mc {

struct GroupLayer final : Layer
{
    struct IDs
    {
        inline static constexpr auto const* type = "Group";
    };

    GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager);
    ~GroupLayer() override = default;

    auto mightHaveChildren() -> bool override;
};

} // namespace mc
