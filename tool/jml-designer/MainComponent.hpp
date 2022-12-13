#pragma once

#include "Document/DocumentEditor.hpp"
#include "Menu/MenuBar.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc {
struct MainComponent final
    : juce::Component
    , juce::DragAndDropContainer
    , juce::ApplicationCommandTarget
{
    MainComponent();
    ~MainComponent() override;

    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

    auto paint(juce::Graphics&) -> void override;
    auto resized() -> void override;

private:
    auto documentLoad() -> void;
    auto documentSaveAs() -> void;

    juce::UndoManager _undoManager;
    juce::ApplicationCommandManager _commandManager{};
    UniquePtr<juce::FileChooser> _fileChooser{};
    MenuBar _menuBar{_commandManager};

    juce::File _documentFile;
    UniquePtr<Document> _document{makeUnique<Document>(juce::ValueTree{"JML"}, &_undoManager)};
    UniquePtr<DocumentEditor> _editor{makeUnique<DocumentEditor>(*_document)};
};

} // namespace mc
