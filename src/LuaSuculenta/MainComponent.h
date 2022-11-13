#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "ComponentContainer.hpp"
#include "ComponentTree.hpp"
#include "MenuBar.hpp"
#include "FileChangeListener.hpp"
#include "Sol3.hpp"

namespace mc {
struct MainComponent : juce::Component,juce::ApplicationCommandTarget {
    MainComponent();
    ~MainComponent() override;

    auto paint(juce::Graphics& g) -> void override;
    auto paintOverChildren(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

private:
    auto reloadScript(juce::File const& path) -> void;
    auto loadScriptPath() -> void;


    juce::ApplicationCommandManager _commandManager{};
    juce::UndoManager _undoManager;
    MenuBar _menuBar{_commandManager};

    sol::state _lua;
    juce::Component* _comp { nullptr };

    ComponentContainer _viewport;
    ComponentTree _componentTree;
    juce::TextButton _select { "Select Script" };
    juce::TextButton _reload { "Reload" };

    juce::File _currentScript;
    std::unique_ptr<FileChangeListener> _fileListener;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

} // namespace mc