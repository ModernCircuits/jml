#include "LuaSuculentaLookAndFeel.hpp"

#include "LuaSuculentaColors.hpp"

namespace mc {
LuaSuculentaLookAndFeel::LuaSuculentaLookAndFeel()
    : juce::LookAndFeel_V4 { {
        LuaSuculentaColors::whiteDirt,      // windowBackground
        LuaSuculentaColors::white,          // widgetBackground
        LuaSuculentaColors::white,          // menuBackground
        juce::Colours::transparentBlack,    // outline
        LuaSuculentaColors::black,          // defaultText
        LuaSuculentaColors::white.darker(), // defaultFill
        LuaSuculentaColors::black,          // highlightedText
        LuaSuculentaColors::whiteDirt,      // highlightedFill
        LuaSuculentaColors::black,          // menuText
    } }
{
    setColour(juce::CodeEditorComponent::backgroundColourId, OneLightColors::editorBackground);
    setColour(juce::CodeEditorComponent::highlightColourId, OneLightColors::editorHighlight);
    setColour(juce::CodeEditorComponent::defaultTextColourId, OneLightColors::editorForeground);
    setColour(juce::CodeEditorComponent::lineNumberBackgroundId, LuaSuculentaColors::transparent);
    setColour(juce::CodeEditorComponent::lineNumberTextId, OneLightColors::editorLineNumber);

    // setColour(juce::TextEditor::ColourIds::, OneLightColors::editorLineNumber);
    // setColour(juce::ComboBox::backgroundColourId, LuaSuculentaColors::bg3);

    // setColour(juce::DrawableButton::backgroundColourId, LuaSuculentaColors::transparent);
    // setColour(juce::DrawableButton::backgroundOnColourId, LuaSuculentaColors::transparent);

    // setColour(juce::Slider::backgroundColourId, LuaSuculentaColors::fg2);
    // setColour(juce::Slider::rotarySliderOutlineColourId, LuaSuculentaColors::fg2);
    // setColour(juce::Slider::rotarySliderFillColourId, LuaSuculentaColors::whiteDirt);
    // setColour(juce::Slider::thumbColourId, LuaSuculentaColors::black);
}

} // namespace mc
