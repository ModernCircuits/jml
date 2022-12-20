#include "DropShadow.hpp"

namespace mc {

DropShadow::DropShadow(juce::ValueTree vt, juce::UndoManager& um) : LayerEffect{std::move(vt), um} {}

auto DropShadow::getName() -> juce::String { return IDs::type; }

auto DropShadow::getImageEffect() -> juce::ImageEffectFilter* { return &_effect; }

} // namespace mc
