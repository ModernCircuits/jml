#include "LookAndFeel_V4.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_LookAndFeel_V4(sol::table& state) -> void { state.new_usertype<juce::LookAndFeel_V4>("LookAndFeel_V4"); }