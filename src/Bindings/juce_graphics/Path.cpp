#include "Path.hpp"

#include <juce_graphics/juce_graphics.h>

auto juce_Path(sol::table& state) -> void
{
    // clang-format off
    auto path = state.new_usertype<juce::Path>("Path",
        sol::constructors<juce::Path()>()
    );
    path["contains"] = sol::overload(
            [] (juce::Path* self, float x, float y) -> bool { return self->contains(x, y); },
            static_cast<bool (juce::Path::*)(float,float,float) const>(&juce::Path::contains),
            static_cast<bool (juce::Path::*)(juce::Point<float>, float) const>(&juce::Path::contains)
    );
    path["intersectsLine"] = sol::overload(
            [] (juce::Path* self, juce::Line<float> line) -> bool { return self->intersectsLine(line); },
            static_cast<bool (juce::Path::*)(juce::Line<float>, float)>(&juce::Path::intersectsLine)
    );
    // clang-format on

    path["isEmpty"]              = &juce::Path::isEmpty;
    path["getBounds"]            = &juce::Path::getBounds;
    path["getBoundsTransformed"] = &juce::Path::getBoundsTransformed;
    path["clear"]                = &juce::Path::clear;
    path["toString"]             = &juce::Path::toString;
}