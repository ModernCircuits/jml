#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <lua_juce_core/lua_juce_core.hpp>

#include "Application/MenuBar.hpp"
#include "Viewer/ComponentContainer.hpp"
#include "Viewer/ComponentTree.hpp"
#include "Viewer/FileChangeListener.hpp"

namespace mc {
struct LuaScriptViewer : juce::Component
{
    LuaScriptViewer();
    ~LuaScriptViewer() override = default;

    [[nodiscard]] auto getScriptFile() const -> juce::File { return _scriptFile; }
    auto setScriptFile(juce::File const& path) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto paintOverChildren(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto handleLuaError(sol::error const& error) -> void;

    sol::state _lua;
    sol::object _compObj;
    juce::Component::SafePointer<juce::Component> _comp{nullptr};

    ComponentContainer _viewport;
    ComponentTree _componentTree;

    juce::File _scriptFile;
    std::unique_ptr<FileChangeListener> _fileListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LuaScriptViewer)
};

} // namespace mc