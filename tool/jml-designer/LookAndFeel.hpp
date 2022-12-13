#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {
inline auto makeColorScheme()
{
    return juce::LookAndFeel_V4::ColourScheme{
        juce::Colours::lightgrey,        // windowBackground
        juce::Colours::white,            // widgetBackground
        juce::Colours::white,            // menuBackground
        juce::Colours::transparentBlack, // outline
        juce::Colours::black,            // defaultText
        juce::Colours::white,            // defaultFill
        juce::Colours::black,            // highlightedText
        juce::Colours::lightgrey,        // highlightedFill
        juce::Colours::black,            // menuText
    };
}

inline auto setComponentColors(juce::LookAndFeel& lnf)
{
    lnf.setColour(juce::DrawableButton::backgroundColourId, juce::Colours::transparentBlack);
    lnf.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentBlack);
    lnf.setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::white);
    lnf.setColour(juce::PropertyComponent::backgroundColourId, juce::Colours::transparentBlack);
    lnf.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    lnf.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    lnf.setColour(juce::TreeView::dragAndDropIndicatorColourId, juce::Colours::black);
}
} // namespace mc
