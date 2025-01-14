#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <mc_gui_testing/mc_gui_testing.hpp>

#include "Application/MenuBar.hpp"
#include "CodeEditor/CodeEditor.hpp"
#include "LookAndFeel/JmlViewerColors.hpp"
#include "LookAndFeel/JmlViewerLookAndFeel.hpp"
#include "Viewer/ComponentContainer.hpp"
#include "Viewer/ComponentTree.hpp"
#include "Viewer/FileChangeListener.hpp"
#include "Viewer/LuaScriptViewer.hpp"

namespace mc {

struct ClientConnection final : juce::InterprocessConnection
{
    ClientConnection() = default;
    ~ClientConnection() override { disconnect(); }

    auto connectionMade() -> void override { DBG("CLIENT MADE"); }
    auto connectionLost() -> void override { DBG("CLIENT LOST"); }
    auto messageReceived(juce::MemoryBlock const& buffer) -> void override
    {
        auto in      = juce::MemoryInputStream{buffer, false};
        auto request = fromValueTree<GetGlobalComponentBounds::Request>(juce::ValueTree::readFromStream(in));
        DBG("CLIENT MSG: " << request.componentID);

        auto response = toValueTree(GetGlobalComponentBounds::Response{juce::Rectangle{0, 0, 500, 500}});
        auto out      = juce::MemoryOutputStream{};
        response.writeToStream(out);
        sendMessage(out.getMemoryBlock());
    }
};

struct MainComponent
    : juce::Component
    , juce::ApplicationCommandTarget
{
    MainComponent();
    ~MainComponent() override;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

private:
    auto doReload(juce::File const& file) -> void;

    auto loadScriptPath() -> void;

    juce::ApplicationCommandManager _commandManager{};
    juce::UndoManager _undoManager;
    JmlViewerLookAndFeel _lnf;

    MenuBar _menuBar{_commandManager};
    juce::TabbedComponent _tabs{juce::TabbedButtonBar::TabsAtLeft};
    LuaScriptViewer _preview;
    CodeEditor _editor;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    ClientConnection _connection;

    JUCE_LEAK_DETECTOR(MainComponent) // NOLINT
};

} // namespace mc
