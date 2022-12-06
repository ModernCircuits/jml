#pragma once

#include <juce_graphics/juce_graphics.h>

namespace mc {
struct LuaSuculentaColors {
    inline static juce::Colour const black       = juce::Colours::black;
    inline static juce::Colour const transparent = juce::Colours::transparentBlack;
    inline static juce::Colour const white       = juce::Colours::white;
    inline static juce::Colour const whiteDirt   = juce::Colour::fromRGB(240, 240, 240);
};

struct OneLightColors {
    inline static juce::Colour const editorBackground = juce::Colour(0xFFFAFAFA);
    inline static juce::Colour const editorForeground = juce::Colour(0xFF383A42);
    inline static juce::Colour const editorHighlight  = juce::Colour(0xFFE5E5E6);
    inline static juce::Colour const editorLineNumber = juce::Colour(0xFF9D9D9F);

    inline static juce::Colour const codeError       = juce::Colour(0xFFFF1414);
    inline static juce::Colour const codeKeyword     = juce::Colour(0xFFA626A4);
    inline static juce::Colour const codeComment     = juce::Colour(0xFFA0A1A7);
    inline static juce::Colour const codeOperator    = juce::Colour(0xFF383A42);
    inline static juce::Colour const codeIdentifier  = juce::Colour(0xFFC18401);
    inline static juce::Colour const codeInteger     = juce::Colour(0xFF986801);
    inline static juce::Colour const codeFloat       = juce::Colour(0xFF986801);
    inline static juce::Colour const codeString      = juce::Colour(0xFF50A14F);
    inline static juce::Colour const codeBracket     = juce::Colour(0xFF383A42);
    inline static juce::Colour const codePunctuation = juce::Colour(0xFF383A42);
};

} // namespace mc
