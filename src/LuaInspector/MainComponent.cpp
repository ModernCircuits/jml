#include "MainComponent.h"

#include "Bindings/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\src\scripts\zentrale.lua)";
}

MainComponent::MainComponent() : _currentScript(defaultScriptPath)
{
    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
    addAndMakeVisible(_select);
    addAndMakeVisible(_reload);

    _select.onClick = [this] { loadScriptPath(); };
    _reload.onClick = [this] { reloadScript(_currentScript); };

    _lua.open_libraries(sol::lib::base, sol::lib::package);
    add_juce_module(_lua);

    setSize(1280, 720);
}

MainComponent::~MainComponent()
{
    if (_comp != nullptr) { _comp->setLookAndFeel(nullptr); }
}

auto MainComponent::paint(juce::Graphics& g) -> void
{
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::black.withAlpha(0.75F));
    g.drawRect(_viewport.getBounds());
}

void MainComponent::resized()
{
    auto area    = getLocalBounds();
    auto btnArea = area.removeFromBottom(area.proportionOfHeight(0.1));
    _select.setBounds(btnArea.removeFromLeft(btnArea.proportionOfWidth(0.5)));
    _reload.setBounds(btnArea);

    _componentTree.setBounds(area.removeFromRight(area.proportionOfWidth(0.2)));
    _viewport.setBounds(area);
}

auto MainComponent::reloadScript(juce::File const& path) -> void
{
    if (_comp != nullptr) {
        _fileListener.reset(nullptr);

        _comp->setLookAndFeel(nullptr);
        _viewport.setViewedComponent(nullptr);
    }

    _lua.collect_garbage();

    path.getParentDirectory().setAsCurrentWorkingDirectory();
    auto script = _lua.load_file(path.getFullPathName().toStdString());
    if (juce::Component* c = script(); c != nullptr) {
        _comp = c;
        _comp->resized();

        _viewport.setViewedComponent(_comp, false);
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