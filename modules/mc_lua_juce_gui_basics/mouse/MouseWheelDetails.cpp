#include "MouseWheelDetails.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {
auto juce_MouseWheelDetails(sol::table& state) -> void
{
    auto wheel          = state.new_usertype<juce::MouseWheelDetails>("MouseWheelDetails");
    wheel["deltaX"]     = &juce::MouseWheelDetails::deltaX;
    wheel["deltaY"]     = &juce::MouseWheelDetails::deltaY;
    wheel["isReversed"] = &juce::MouseWheelDetails::isReversed;
    wheel["isSmooth"]   = &juce::MouseWheelDetails::isSmooth;
    wheel["isInertial"] = &juce::MouseWheelDetails::isInertial;
}
} // namespace mc::lua::bindings
