#include "CodeEditor.hpp"

#include "LookAndFeel/JmlViewerColors.hpp"

namespace mc {

static auto makeCodeEditorColorScheme() -> juce::CodeEditorComponent::ColourScheme
{
    static juce::CodeEditorComponent::ColourScheme::TokenType const types[] = {
        {"Error", juce::Colour(0xffcc0000)},      {"Comment", OneLightColors::codeComment},
        {"Keyword", OneLightColors::codeKeyword}, {"Operator", OneLightColors::codeOperator},
        {"Identifier", juce::Colour(0xff000000)}, {"Integer", OneLightColors::codeInteger},
        {"Float", OneLightColors::codeFloat},     {"String", OneLightColors::codeString},
        {"Bracket", OneLightColors::codeBracket}, {"Punctuation", juce::Colour(0xff004400)},
    };

    auto cs = juce::CodeEditorComponent::ColourScheme{};
    for (auto const& t : types) { cs.set(t.name, t.colour); }
    return cs;
}

CodeEditor::CodeEditor()
{
    _editor.setLineNumbersShown(true);
    _editor.setColourScheme(makeCodeEditorColorScheme());
    addAndMakeVisible(_editor);
}

auto CodeEditor::file(juce::File file) -> void
{
    _file = std::move(file);
    if (auto stream = _file.createInputStream(); stream) { _document.loadFromStream(*stream); }
}

auto CodeEditor::paint(juce::Graphics& g) -> void { g.fillAll(JmlViewerColors::whiteDirt); }
auto CodeEditor::resized() -> void { _editor.setBounds(getLocalBounds().reduced(16)); }

} // namespace mc
