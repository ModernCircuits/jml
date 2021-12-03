#include "ColourGradient.hpp"

#include <juce_graphics/juce_graphics.h>

auto juce_ColourGradient(sol::table& state) -> void
{
    // TODO(tobi):
    // createLookupTable

    // clang-format off
    auto gradient = state.new_usertype<juce::ColourGradient>("ColourGradient",
        sol::constructors<
            juce::ColourGradient(),
            juce::ColourGradient(juce::Colour, float, float, juce::Colour, float, float, bool),
            juce::ColourGradient(juce::Colour, juce::Point<float>, juce::Colour, juce::Point<float>, bool)
        >()
    );
    // clang-format on

    gradient["clearColours"]        = &juce::ColourGradient::clearColours;
    gradient["addColour"]           = &juce::ColourGradient::addColour;
    gradient["removeColour"]        = &juce::ColourGradient::removeColour;
    gradient["multiplyOpacity"]     = &juce::ColourGradient::multiplyOpacity;
    gradient["getNumColours"]       = &juce::ColourGradient::getNumColours;
    gradient["getColourPosition"]   = &juce::ColourGradient::getColourPosition;
    gradient["getColour"]           = &juce::ColourGradient::getColour;
    gradient["setColour"]           = &juce::ColourGradient::setColour;
    gradient["getColourAtPosition"] = &juce::ColourGradient::getColourAtPosition;
    gradient["isOpaque"]            = &juce::ColourGradient::isOpaque;
    gradient["isInvisible"]         = &juce::ColourGradient::isInvisible;

    gradient["point1"]   = &juce::ColourGradient::point1;
    gradient["point2"]   = &juce::ColourGradient::point2;
    gradient["isRadial"] = &juce::ColourGradient::isRadial;
}
