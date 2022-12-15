#include "ColourGradient.hpp"

#include <juce_graphics/juce_graphics.h>
namespace mc::lua::bindings {
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
    gradient.set_function("vertical", sol::overload(
            static_cast<juce::ColourGradient (*)(juce::Colour, float, juce::Colour, float)>(&juce::ColourGradient::vertical),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<int>)>(&juce::ColourGradient::template vertical<int>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<float>)>(&juce::ColourGradient::template vertical<float>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<double>)>(&juce::ColourGradient::template vertical<double>)
        )
    );
    gradient.set_function("horizontal", sol::overload(
            static_cast<juce::ColourGradient (*)(juce::Colour, float, juce::Colour, float)>(&juce::ColourGradient::horizontal),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<int>)>(&juce::ColourGradient::template horizontal<int>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<float>)>(&juce::ColourGradient::template horizontal<float>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<double>)>(&juce::ColourGradient::template horizontal<double>)
        )
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
} // namespace mc::lua::bindings
