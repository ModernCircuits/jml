#include "GlowLayerEffect.hpp"

namespace mc {

GlowLayerEffect::GlowLayerEffect(juce::ValueTree vt, juce::UndoManager& um) : LayerEffect{std::move(vt), um} {}

auto GlowLayerEffect::getName() -> juce::String { return IDs::type; }

auto GlowLayerEffect::getImageEffect() -> juce::ImageEffectFilter* { return &_effect; }

} // namespace mc
