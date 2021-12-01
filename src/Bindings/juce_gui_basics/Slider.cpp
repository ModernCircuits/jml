#include "Slider.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_Slider(sol::table& state) -> void
{
    // clang-format off
    auto slider = state.new_usertype<juce::Slider>("Slider",
        sol::constructors<
            juce::Slider(),
            juce::Slider(juce::String const&)
        >(),
        sol::base_classes, sol::bases<juce::Component>()
    );
    // clang-format on
    auto params                 = state.new_usertype<juce::Slider::RotaryParameters>("SliderRotaryParameters");
    params["startAngleRadians"] = &juce::Slider::RotaryParameters::startAngleRadians;
    params["endAngleRadians"]   = &juce::Slider::RotaryParameters::endAngleRadians;
    params["stopAtEnd"]         = &juce::Slider::RotaryParameters::stopAtEnd;
}
