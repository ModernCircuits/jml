#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct ComponentContainer final : juce::Component
{
    ComponentContainer()           = default;
    ~ComponentContainer() override = default;

    auto component(juce::Component* component) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    juce::Component* _component{nullptr};
};

} // namespace mc
