#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <lua_juce_sol2/lua_juce_sol2.hpp>

#include "Application/MenuBar.hpp"
#include "Preview/ComponentContainer.hpp"
#include "Preview/ComponentTree.hpp"
#include "Preview/FileChangeListener.hpp"

namespace mc {
struct LuaPreview : juce::Component {
    LuaPreview();
    ~LuaPreview() override;

    auto script(juce::File const& path) -> void;
    auto script() const -> juce::File { return _currentScript; }

    auto paint(juce::Graphics& g) -> void override;
    auto paintOverChildren(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    sol::state _lua;
    sol::object _compObj;
    juce::Component::SafePointer<juce::Component> _comp { nullptr };

    ComponentContainer _viewport;
    ComponentTree _componentTree;

    juce::File _currentScript;
    std::unique_ptr<FileChangeListener> _fileListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LuaPreview)
};

} // namespace mc
