#include "DropShadowLayerEffect.hpp"

namespace mc {

DropShadowLayerEffect::DropShadowLayerEffect(juce::ValueTree vt, juce::UndoManager& um) : LayerEffect{std::move(vt), um}
{
}

auto DropShadowLayerEffect::getName() -> juce::String { return IDs::type; }

auto DropShadowLayerEffect::getImageEffect() -> juce::ImageEffectFilter* { return &_effect; }

} // namespace mc
