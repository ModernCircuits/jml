#pragma once

#include "Layer/Effect/LayerEffect.hpp"

namespace mc {

struct DropShadowLayerEffectIDs
{
    inline static constexpr auto const* type = "DropShadow";

    inline static constexpr auto const* color  = "color";
    inline static constexpr auto const* radius = "radius";
    inline static constexpr auto const* offset = "offset";
};

struct DropShadowLayerEffect final : LayerEffect
{
    using IDs = DropShadowLayerEffectIDs;

    DropShadowLayerEffect(juce::ValueTree vt, juce::UndoManager& um);
    ~DropShadowLayerEffect() override = default;

    [[nodiscard]] auto getName() -> juce::String override;
    [[nodiscard]] auto getImageEffect() -> juce::ImageEffectFilter* override;

private:
    juce::DropShadowEffect _effect;
};

} // namespace mc
