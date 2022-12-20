#pragma once

#include "Layer/Effect/LayerEffect.hpp"

namespace mc {

struct DropShadowIDs
{
    inline static constexpr auto const* type = "DropShadow";

    inline static constexpr auto const* color  = "color";
    inline static constexpr auto const* radius = "radius";
    inline static constexpr auto const* offset = "offset";
};

struct DropShadow final : LayerEffect
{
    using IDs = DropShadowIDs;

    DropShadow(juce::ValueTree vt, juce::UndoManager& um);
    ~DropShadow() override = default;

    [[nodiscard]] auto getName() -> juce::String override;
    [[nodiscard]] auto getImageEffect() -> juce::ImageEffectFilter* override;

private:
    juce::DropShadowEffect _effect;
};

} // namespace mc
