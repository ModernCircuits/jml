#include "LuaPreview.hpp"

#include "Lua/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\example\jml\main.lua)";
}

LuaPreview::LuaPreview() : _currentScript(defaultScriptPath)
{
    _lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    add_juce_module(_lua);

    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
}

LuaPreview::~LuaPreview() = default;

auto LuaPreview::script(juce::File const& path) -> void
{
    DBG("Reload");

    if (_comp != nullptr) {
        _fileListener.reset(nullptr);
        _viewport.component(nullptr);
    }

    _lua.collect_garbage();

    if (not path.existsAsFile()) { return; }
    path.getParentDirectory().setAsCurrentWorkingDirectory();

    auto luaScript = _lua.load_file(path.getFullPathName().toStdString());
    jassert(luaScript.valid());
    if (not luaScript.valid()) { return; }

    auto factory = luaScript.get<sol::protected_function>();
    auto result  = factory();
    jassert(result.valid());
    if (not result.valid()) { return; }

    _compObj = result;
    _comp    = _compObj.as<juce::Component*>();
    _comp->resized();

    _viewport.component(_comp);
    _componentTree.setRootComponent(_comp);

    _currentScript          = path;
    _fileListener           = std::make_unique<FileChangeListener>(_currentScript);
    _fileListener->onChange = [this] { script(_currentScript); };

    resized();
}

auto LuaPreview::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

auto LuaPreview::paintOverChildren(juce::Graphics& g) -> void
{
    g.setColour(juce::Colours::black.withAlpha(0.75F));
    // g.drawRect(_viewport.getBounds());
}

void LuaPreview::resized()
{
    auto area = getLocalBounds();
    _componentTree.setBounds(area.removeFromRight(area.proportionOfWidth(0.2)));
    _viewport.setBounds(area);
}

} // namespace mc
