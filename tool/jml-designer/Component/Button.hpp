#pragma once

#include "BinaryData.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct DrawableButtonColors
{
    juce::Colour offFill;
    juce::Colour offText;
    juce::Colour onFill;
    juce::Colour onText;
};

inline auto setImages(juce::DrawableButton& button, char const* svgFile, DrawableButtonColors colors) -> void
{
    auto svgSize        = 0;
    auto const* svgData = mcbd::getNamedResource(svgFile, svgSize);
    jassert(svgData != nullptr);

    auto on  = juce::Drawable::createFromImageData(svgData, static_cast<size_t>(svgSize));
    auto off = on->createCopy();

    on->replaceColour(juce::Colours::black, colors.onFill);
    on->replaceColour(juce::Colours::white, colors.onText);
    off->replaceColour(juce::Colours::black, colors.offFill);
    off->replaceColour(juce::Colours::white, colors.offText);

    button.setImages(off.get(), nullptr, on.get(), nullptr, on.get());
}

} // namespace mc
