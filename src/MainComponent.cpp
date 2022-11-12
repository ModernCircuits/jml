#include "MainComponent.h"

#include "Bindings/Juce.hpp"

auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\src\scripts\supernova.lua)";

MainComponent::MainComponent() : _currentScript(defaultScriptPath)
{
    setSize(1280, 720);
    addAndMakeVisible(_select);
    _select.onClick = [this] { loadScriptPath(); };
    addAndMakeVisible(_reload);
    _reload.onClick = [this] { reloadScript(_currentScript); };

    _lua.open_libraries(sol::lib::base, sol::lib::package);
    add_juce_module(_lua);
}

MainComponent::~MainComponent()
{
    if (_comp != nullptr) { _comp->setLookAndFeel(nullptr); }
}

void MainComponent::resized()
{
    auto area    = getLocalBounds();
    auto btnArea = area.removeFromBottom(area.proportionOfHeight(0.1));
    _select.setBounds(btnArea.removeFromLeft(btnArea.proportionOfWidth(0.5)));
    _reload.setBounds(btnArea);

    if (_componentTree != nullptr) { _componentTree->setBounds(area.removeFromRight(area.proportionOfWidth(0.2))); }
    if (_comp != nullptr) { _comp->setBounds(area); }
}

auto MainComponent::reloadScript(juce::File const& path) -> void
{
    if (_comp != nullptr) {
        removeChildComponent(_componentTree.get());
        _componentTree.reset(nullptr);

        _comp->setLookAndFeel(nullptr);
        removeChildComponent(_comp);
    }

    _lua.collect_garbage();

    path.getParentDirectory().setAsCurrentWorkingDirectory();
    auto script = _lua.load_file(path.getFullPathName().toStdString());
    if (juce::Component* c = script(); c != nullptr) {
        _comp = c;
        addAndMakeVisible(*_comp);

        _componentTree = std::make_unique<ComponentTree>(c);
        addAndMakeVisible(*_componentTree);

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