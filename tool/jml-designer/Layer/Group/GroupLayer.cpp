#include "GroupLayer.hpp"

#include "Layer/Drawable/DrawableLayer.hpp"

namespace mc {

GroupLayer::GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager) : Layer{v, undoManager} {}

auto GroupLayer::mightHaveChildren() -> bool { return true; }

} // namespace mc
