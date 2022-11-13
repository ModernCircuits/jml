#pragma once

#include <juce_graphics/juce_graphics.h>

namespace mc {
struct LuaSuculentaColors {
    inline static juce::Colour const black       = juce::Colours::black;
    inline static juce::Colour const transparent = juce::Colours::transparentBlack;
    inline static juce::Colour const white       = juce::Colours::white;
    inline static juce::Colour const whiteDirt   = juce::Colour::fromRGB(240, 240, 240);
};

} // namespace mc