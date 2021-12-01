#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "Sol3.hpp"

struct MainComponent : juce::Component {
    MainComponent();
    ~MainComponent() override = default;

    void resized() override;

private:
    auto reloadScript(juce::File const& path) -> void;
    auto loadScriptPath() -> void;

    sol::state _lua;
    juce::Component* _comp { nullptr };
    juce::TextButton _select { "Select Script" };
    juce::TextButton _reload { "Reload" };

    juce::File _currentScript;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
