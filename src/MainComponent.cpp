#include "MainComponent.h"

#include "Bindings/Juce.hpp"

auto const* scriptPath = R"(/home/tobante/Developer/tobanteAudio/lua-juce/src/scripts/demo_Components.lua)";

MainComponent::MainComponent()
{
    addAndMakeVisible(_button);
    setSize(1280, 720);
    _button.onClick = [this] { reloadScript(juce::File { scriptPath }); };
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    _button.setBounds(area.removeFromBottom(area.proportionOfHeight(0.1)));
    if (_comp != nullptr) { _comp->setBounds(area); }
}

auto MainComponent::reloadScript(juce::File const& path) -> void
{
    if (_comp != nullptr) { removeChildComponent(_comp); }

    _lua.open_libraries(sol::lib::base);
    add_juce_module(_lua);

    auto script = _lua.load_file(path.getFullPathName().toStdString());
    if (juce::Component* c = script(); c != nullptr) {
        _comp = c;
        addAndMakeVisible(*_comp);
        resized();
    }
}