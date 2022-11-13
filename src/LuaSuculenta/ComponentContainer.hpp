#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct ComponentContainer final : juce::Component {
    ComponentContainer()           = default;
    ~ComponentContainer() override = default;

    auto component(juce::Component* component) -> void
    {
        if (_component != nullptr) { removeChildComponent(_component); }
        if (_component = component; _component != nullptr) {
            addAndMakeVisible(_component);
            resized();
        }
    }

    auto paint(juce::Graphics& g) -> void override { g.fillAll(juce::Colour::fromRGB(240, 240, 240)); }

    auto resized() -> void override
    {
        if (_component == nullptr) { return; }

        auto const area = getLocalBounds();
        auto const size = juce::Rectangle<int> { 0, 0, _component->getWidth(), _component->getHeight() };
        _component->setBounds(size.withCentre(area.getCentre()));
    }

private:
    juce::Component* _component { nullptr };
};

} // namespace mc
