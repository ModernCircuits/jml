#pragma once

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct LayerEffect : ValueTreeObject
{
    LayerEffect(juce::ValueTree vt, juce::UndoManager& um);
    virtual ~LayerEffect() = default;

    [[nodiscard]] virtual auto getName() -> juce::String                    = 0;
    [[nodiscard]] virtual auto getImageEffect() -> juce::ImageEffectFilter* = 0;
};

} // namespace mc
