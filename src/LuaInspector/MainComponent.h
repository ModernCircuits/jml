#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "ComponentTree.hpp"
#include "FileChangeListener.hpp"
#include "Sol3.hpp"

namespace mc {
struct MainComponent : juce::Component {
    MainComponent();
    ~MainComponent() override;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto reloadScript(juce::File const& path) -> void;
    auto loadScriptPath() -> void;

    sol::state _lua;
    juce::Component* _comp { nullptr };

    juce::Viewport _viewport;
    ComponentTree _componentTree;
    juce::TextButton _select { "Select Script" };
    juce::TextButton _reload { "Reload" };

    juce::File _currentScript;
    std::unique_ptr<FileChangeListener> _fileListener;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

} // namespace mc