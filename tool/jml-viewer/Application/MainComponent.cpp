#include "MainComponent.hpp"

#include "Application/CommandIDs.hpp"

namespace mc {

MainComponent::MainComponent()
{
    _commandManager.registerAllCommandsForTarget(this);
    addKeyListener(_commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    _tabs.setTabBarDepth(50);
    _tabs.addTab("Viewer", JmlViewerColors::black, &_preview, false);
    _tabs.addTab("Code", JmlViewerColors::black, &_editor, false);

    addAndMakeVisible(_menuBar);
    addAndMakeVisible(_tabs);

    setLookAndFeel(&_lnf);
    setSize(1280, 720);

    if (not _connection.connectToSocket("127.0.0.1", 14430, 1000)) { DBG("DID NOT CONNECT TO SERVER"); }
}

MainComponent::~MainComponent() { setLookAndFeel(nullptr); }

auto MainComponent::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

auto MainComponent::resized() -> void
{
    auto area = getLocalBounds();
    _menuBar.setBounds(area.removeFromTop(getLookAndFeel().getDefaultMenuBarHeight()));
    _tabs.setBounds(area);
}

auto MainComponent::getNextCommandTarget() -> juce::ApplicationCommandTarget*
{
    return findFirstTargetParentComponent();
}

auto MainComponent::getAllCommands(juce::Array<juce::CommandID>& c) -> void
{
    c.addArray({
        CommandIDs::open,
        CommandIDs::reload,
        CommandIDs::save,
        CommandIDs::saveAs,
        CommandIDs::redo,
        CommandIDs::undo,
    });
}

auto MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void
{
    using juce::KeyPress;
    using juce::ModifierKeys;

    switch (commandID) {
        case CommandIDs::open:
            result.setInfo("Open", "Opens a script file", "File", 0);
            result.addDefaultKeypress('o', ModifierKeys::commandModifier);
            break;
        case CommandIDs::reload:
            result.setInfo("Reload", "Reload script file", "File", 0);
            result.addDefaultKeypress('r', ModifierKeys::commandModifier);
            break;
        case CommandIDs::save:
            result.setInfo("Save", "Saves a script file", "File", 0);
            result.addDefaultKeypress('s', ModifierKeys::commandModifier);
            break;
        case CommandIDs::saveAs:
            result.setInfo("Save As", "Saves a script file to a new location", "File", 0);
            result.addDefaultKeypress('s', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
        case CommandIDs::undo:
            result.setInfo("Undo", "Undo one step", "Edit", 0);
            result.addDefaultKeypress('z', ModifierKeys::commandModifier);
            break;
        case CommandIDs::redo:
            result.setInfo("Redo", "Redo one step", "Edit", 0);
            result.addDefaultKeypress('z', ModifierKeys::commandModifier | ModifierKeys::shiftModifier);
            break;
        default: break;
    }
}

auto MainComponent::perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool
{
    switch (info.commandID) {
        case CommandIDs::open: loadScriptPath(); break;
        case CommandIDs::reload: doReload(_preview.getScriptFile()); break;
        case CommandIDs::save:
        case CommandIDs::saveAs: /*saveProject();*/ break;
        case CommandIDs::undo: _undoManager.undo(); break;
        case CommandIDs::redo: _undoManager.redo(); break;
        default: return false;
    }

    return true;
}

auto MainComponent::doReload(juce::File const& file) -> void
{
    _preview.setScriptFile(file);
    _editor.file(file);
}

auto MainComponent::loadScriptPath() -> void
{
    auto const* msg = "Please select the lua script you want to load...";
    auto const dir  = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    _fileChooser    = std::make_unique<juce::FileChooser>(msg, dir, "*.lua");
    _fileChooser->launchAsync(juce::FileBrowserComponent::openMode, [this](auto const& chooser) {
        if (auto results = chooser.getResults(); results.size() == 1) { doReload(results[0]); }
    });
}
} // namespace mc
