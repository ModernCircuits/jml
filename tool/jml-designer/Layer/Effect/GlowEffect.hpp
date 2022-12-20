#pragma once

#include "Layer/Effect/LayerEffect.hpp"

namespace mc {

struct GlowEffectIDs
{
    inline static constexpr auto const* type   = "Glow";
    inline static constexpr auto const* color  = "color";
    inline static constexpr auto const* radius = "radius";
    inline static constexpr auto const* offset = "offset";
};

struct GlowEffect final : LayerEffect
{
    using IDs = GlowEffectIDs;

    GlowEffect(juce::ValueTree vt, juce::UndoManager& um);
    ~GlowEffect() override = default;

    [[nodiscard]] auto getName() -> juce::String override;
    [[nodiscard]] auto getImageEffect() -> juce::ImageEffectFilter* override;

private:
    juce::GlowEffect _effect;
};

} // namespace mc
