#include "LayerEffect.hpp"

namespace mc {

LayerEffect::LayerEffect(juce::ValueTree vt, juce::UndoManager& um) : ValueTreeObject{std::move(vt), &um} {}

} // namespace mc
