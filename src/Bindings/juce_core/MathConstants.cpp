#include "MathConstants.hpp"

#include <juce_core/juce_core.h>

auto juce_MathConstants(sol::table& state) -> void
{
    auto constants      = state.create_named("MathConstants");
    constants["pi"]     = &juce::MathConstants<double>::pi;
    constants["twoPi"]  = &juce::MathConstants<double>::twoPi;
    constants["halfPi"] = &juce::MathConstants<double>::halfPi;
    constants["euler"]  = &juce::MathConstants<double>::euler;
    constants["sqrt2"]  = &juce::MathConstants<double>::sqrt2;
}