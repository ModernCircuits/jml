#include "JmlViewerLookAndFeel.hpp"

#include "LookAndFeel/JmlViewerColors.hpp"

namespace mc {
JmlViewerLookAndFeel::JmlViewerLookAndFeel()
    : juce::LookAndFeel_V4{{
        JmlViewerColors::whiteDirt,      // windowBackground
        JmlViewerColors::white,          // widgetBackground
        JmlViewerColors::white,          // menuBackground
        juce::Colours::transparentBlack, // outline
        JmlViewerColors::black,          // defaultText
        JmlViewerColors::white.darker(), // defaultFill
        JmlViewerColors::black,          // highlightedText
        JmlViewerColors::whiteDirt,      // highlightedFill
        JmlViewerColors::black,          // menuText
    }}
{
    setColour(juce::CodeEditorComponent::backgroundColourId, OneLightColors::editorBackground);
    setColour(juce::CodeEditorComponent::highlightColourId, OneLightColors::editorHighlight);
    setColour(juce::CodeEditorComponent::defaultTextColourId, OneLightColors::editorForeground);
    setColour(juce::CodeEditorComponent::lineNumberBackgroundId, JmlViewerColors::transparent);
    setColour(juce::CodeEditorComponent::lineNumberTextId, OneLightColors::editorLineNumber);

    // setColour(juce::TextEditor::ColourIds::, OneLightColors::editorLineNumber);
    // setColour(juce::ComboBox::backgroundColourId, JmlViewerColors::bg3);

    // setColour(juce::DrawableButton::backgroundColourId, JmlViewerColors::transparent);
    // setColour(juce::DrawableButton::backgroundOnColourId, JmlViewerColors::transparent);

    // setColour(juce::Slider::backgroundColourId, JmlViewerColors::fg2);
    // setColour(juce::Slider::rotarySliderOutlineColourId, JmlViewerColors::fg2);
    // setColour(juce::Slider::rotarySliderFillColourId, JmlViewerColors::whiteDirt);
    // setColour(juce::Slider::thumbColourId, JmlViewerColors::black);
}

} // namespace mc
