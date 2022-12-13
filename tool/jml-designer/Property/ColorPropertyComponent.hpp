#pragma once

#include "Property/ValuePropertyComponent.hpp"

namespace mc {

struct ColorPropertyComponent final : ValuePropertyComponent
{
    ColorPropertyComponent(juce::Value const& valueToControl, juce::String const& propertyName, bool showAlpha = false);
    ~ColorPropertyComponent() override = default;

    auto refresh() -> void override;
    auto paint(juce::Graphics& g) -> void override;

private:
    struct Container final
        : juce::Component
        , juce::ChangeListener
    {
        Container(juce::Value& v, bool a);
        ~Container() override = default;

        auto paint(juce::Graphics& g) -> void override;
        auto mouseUp(juce::MouseEvent const& e) -> void override;
        auto changeListenerCallback(juce::ChangeBroadcaster* source) -> void override;

        juce::Value& value;
        bool alpha;
    };

    Container _container;
};
} // namespace mc
