#pragma once

#include "Layer/Effect/LayerEffect.hpp"

namespace mc {

struct GlowLayerEffectIDs
{
    inline static constexpr auto const* type   = "Glow";
    inline static constexpr auto const* color  = "color";
    inline static constexpr auto const* radius = "radius";
    inline static constexpr auto const* offset = "offset";
};

struct GlowLayerEffect final : LayerEffect
{
    using IDs = GlowLayerEffectIDs;

    GlowLayerEffect(juce::ValueTree vt, juce::UndoManager& um);
    ~GlowLayerEffect() override = default;

    [[nodiscard]] auto getName() -> juce::String override;
    [[nodiscard]] auto getImageEffect() -> juce::ImageEffectFilter* override;

private:
    juce::GlowEffect _effect;
};

} // namespace mc
