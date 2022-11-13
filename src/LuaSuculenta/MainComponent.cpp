#include "MainComponent.h"

#include "CommandIDs.hpp"

#include "Bindings/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\example\zentrale.lua)";
}

MainComponent::MainComponent() : _currentScript(defaultScriptPath)
{
    _commandManager.registerAllCommandsForTarget(this);
    addKeyListener(_commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    addAndMakeVisible(_menuBar);
    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
    addAndMakeVisible(_select);
    addAndMakeVisible(_reload);

    _select.onClick = [this] { loadScriptPath(); };
    _reload.onClick = [this] { reloadScript(_currentScript); };

    _lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    add_juce_module(_lua);

    setSize(1280, 720);
}

MainComponent::~MainComponent()
{
    if (_comp != nullptr) { _comp->setLookAndFeel(nullptr); }
}

auto MainComponent::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

auto MainComponent::paintOverChildren(juce::Graphics& g) -> void
{
    g.setColour(juce::Colours::black.withAlpha(0.75F));
    g.drawRect(_viewport.getBounds());
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    _menuBar.setBounds(area.removeFromTop(getLookAndFeel().getDefaultMenuBarHeight()));

    auto settings = area.removeFromRight(area.proportionOfWidth(0.2));
    auto buttons  = settings.removeFromTop(50);
    _select.setBounds(buttons.removeFromLeft(buttons.proportionOfWidth(0.5)));
    _reload.setBounds(buttons);
    _componentTree.setBounds(settings);

    _viewport.setBounds(area);
}

auto MainComponent::getNextCommandTarget() -> juce::ApplicationCommandTarget* { return findFirstTargetParentComponent(); }

auto MainComponent::getAllCommands(juce::Array<juce::CommandID>& c) -> void
{
    c.addArray({
        CommandIDs::open,
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
        result.setInfo("Open", "Opens a project file", "File", 0);
        result.addDefaultKeypress('o', ModifierKeys::commandModifier);
        break;
    case CommandIDs::save:
        result.setInfo("Save", "Saves a project file", "File", 0);
        result.addDefaultKeypress('s', ModifierKeys::commandModifier);
        break;
    case CommandIDs::saveAs:
        result.setInfo("Save As", "Saves a project file to a new location", "File", 0);
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
    case CommandIDs::open: /*loadProject();*/ break;
    case CommandIDs::save:
    case CommandIDs::saveAs: /*saveProject();*/ break;
    case CommandIDs::undo: _undoManager.undo(); break;
    case CommandIDs::redo: _undoManager.redo(); break;
    default: return false;
    }

    return true;
}

auto MainComponent::reloadScript(juce::File const& path) -> void
{
    if (_comp != nullptr) {
        _fileListener.reset(nullptr);

        _comp->setLookAndFeel(nullptr);
        _viewport.component(nullptr);
    }

    _lua.collect_garbage();

    path.getParentDirectory().setAsCurrentWorkingDirectory();
    auto script = _lua.load_file(path.getFullPathName().toStdString());
    if (juce::Component* c = script(); c != nullptr) {
        _comp = c;
        _comp->resized();

        _viewport.component(_comp);
        _componentTree.setRootComponent(_comp);

        _fileListener           = std::make_unique<FileChangeListener>(path);
        _fileListener->onChange = [this] { reloadScript(_currentScript); };

        resized();
    }
}

auto MainComponent::loadScriptPath() -> void
{
    auto const* msg = "Please select the lua script you want to load...";
    auto const dir  = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    _fileChooser    = std::make_unique<juce::FileChooser>(msg, dir, "*.lua");
    _fileChooser->launchAsync(juce::FileBrowserComponent::openMode, [this](auto const& chooser) {
        if (auto results = chooser.getResults(); results.size() == 1) {
            _currentScript = results[0];
            reloadScript(_currentScript);
        }
    });
}
} // namespace mc