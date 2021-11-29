#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

struct MainComponent : juce::Component {
    MainComponent();
    ~MainComponent() = default;

    void resized() override;

private:
    std::unique_ptr<juce::Component> _comp { nullptr };
    juce::TextButton _button { "Reload" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
