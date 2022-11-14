#include "CodeEditor.hpp"

#include "LuaSuculentaColors.hpp"

namespace mc {

CodeEditor::CodeEditor()
{
    addAndMakeVisible(_editor);
    _editor.setLineNumbersShown(true);
}

auto CodeEditor::file(juce::File file) -> void
{
    _file = std::move(file);
    if (auto stream = _file.createInputStream(); stream) { _document.loadFromStream(*stream); }
}

auto CodeEditor::paint(juce::Graphics& g) -> void { g.fillAll(LuaSuculentaColors::whiteDirt); }
auto CodeEditor::resized() -> void { _editor.setBounds(getLocalBounds().reduced(16)); }

} // namespace mc
