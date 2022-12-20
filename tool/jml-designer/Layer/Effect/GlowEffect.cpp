#include "GlowEffect.hpp"

namespace mc {

GlowEffect::GlowEffect(juce::ValueTree vt, juce::UndoManager& um) : LayerEffect{std::move(vt), um} {}

auto GlowEffect::getName() -> juce::String { return IDs::type; }

auto GlowEffect::getImageEffect() -> juce::ImageEffectFilter* { return &_effect; }

} // namespace mc
