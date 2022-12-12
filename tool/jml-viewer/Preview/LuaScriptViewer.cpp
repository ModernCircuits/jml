#include "LuaScriptViewer.hpp"

#include "Lua/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\example\layout_grid.lua)";
}

LuaScriptViewer::LuaScriptViewer() : _scriptFile(defaultScriptPath)
{
    _lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    add_juce_module(_lua);

    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
}

auto LuaScriptViewer::setScriptFile(juce::File const& path) -> void
{
    DBG("Reload");

    if (_comp != nullptr) {
        _fileListener.reset(nullptr);
        _viewport.component(nullptr);
    }

    if (!path.existsAsFile()) { return; }
    path.getParentDirectory().setAsCurrentWorkingDirectory();

    _lua.collect_garbage();
    auto script = _lua.load_file(path.getFullPathName().toStdString());
    if (!script.valid()) { return handleLuaError(script); }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (!result.valid()) { return handleLuaError(result); }

    _compObj = result;
    _comp    = _compObj.as<juce::Component*>();
    _comp->resized();

    _viewport.component(_comp);
    _componentTree.setRootComponent(_comp);

    _scriptFile             = path;
    _fileListener           = std::make_unique<FileChangeListener>(_scriptFile);
    _fileListener->onChange = [this] { setScriptFile(_scriptFile); };

    resized();
}

auto LuaScriptViewer::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

auto LuaScriptViewer::paintOverChildren(juce::Graphics& g) -> void
{
    g.setColour(juce::Colours::black.withAlpha(0.75F));
    // g.drawRect(_viewport.getBounds());
}

void LuaScriptViewer::resized()
{
    auto area = getLocalBounds();
    _componentTree.setBounds(area.removeFromRight(area.proportionOfWidth(0.2)));
    _viewport.setBounds(area);
}

auto LuaScriptViewer::handleLuaError(sol::error const& error) -> void { DBG(error.what()); }

} // namespace mc
