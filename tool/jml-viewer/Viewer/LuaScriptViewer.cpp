#include "LuaScriptViewer.hpp"

#include "Bindings/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\example\layout_grid.lua)";
}

LuaScriptViewer::LuaScriptViewer() : _scriptFile(defaultScriptPath)
{
    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
    startTimer(2000);
}

auto LuaScriptViewer::setScriptFile(juce::File const& file) -> void
{
    auto componentTreeState = _componentTree.getOpennessState(true);

    _fileListener.reset(nullptr);
    _viewport.setContentComponent(nullptr);

    if (not file.existsAsFile()) { return; }
    file.getParentDirectory().setAsCurrentWorkingDirectory();

    reloadLuaState();
    auto script = _lua->state.load_file(file.getFullPathName().toStdString());
    if (not script.valid()) { return handleLuaError(script); }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) { return handleLuaError(result); }

    _lua->obj       = result;
    _lua->component = _lua->obj.as<juce::Component*>();
    _lua->component->resized();

    _viewport.setContentComponent(_lua->component);
    _componentTree.setRootComponent(_lua->component);

    _scriptFile             = file;
    _fileListener           = std::make_unique<FileChangeListener>(_scriptFile);
    _fileListener->onChange = [this] { setScriptFile(_scriptFile); };

    resized();

    if (componentTreeState == nullptr) { return; }
    _componentTree.restoreOpennessState(*componentTreeState, false);
}

auto LuaScriptViewer::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

auto LuaScriptViewer::resized() -> void
{
    auto area = getLocalBounds();
    _componentTree.setBounds(area.removeFromRight(area.proportionOfWidth(0.2)));
    _viewport.setBounds(area);
}

auto LuaScriptViewer::timerCallback() -> void
{
    if (_lua == nullptr) { return; }
    _lua->state.collect_garbage();
}

auto LuaScriptViewer::reloadLuaState() -> void
{
    _lua = std::make_unique<LuaState>();
    _lua->state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    add_juce_module(_lua->state);
}

auto LuaScriptViewer::handleLuaError(sol::error const& error) -> void { DBG(error.what()); }

} // namespace mc
