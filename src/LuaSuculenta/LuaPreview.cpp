#include "LuaPreview.hpp"

#include "Bindings/Juce.hpp"

namespace mc {
namespace {
auto const* defaultScriptPath = R"(C:\Developer\moderncircuits\tests\juce-lua\example\simple.lua)";
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
    if (juce::Component* c = luaScript(); c != nullptr) {
        _comp = c;
        _comp->resized();

        _viewport.component(_comp);
        _componentTree.setRootComponent(_comp);

        _fileListener           = std::make_unique<FileChangeListener>(path);
        _fileListener->onChange = [this] { script(_currentScript); };

        resized();
    }
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
