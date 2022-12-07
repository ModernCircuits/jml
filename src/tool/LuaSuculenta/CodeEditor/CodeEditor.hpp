#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc {

struct CodeEditor : juce::Component
{
    CodeEditor();
    ~CodeEditor() override = default;

    auto file(juce::File file) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    juce::File _file;
    juce::CodeDocument _document;
    juce::LuaTokeniser _tokenizer;
    juce::CodeEditorComponent _editor{_document, &_tokenizer};
};

} // namespace mc
