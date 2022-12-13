#include "Property/ValuePropertyComponent.hpp"

namespace mc {

ValuePropertyComponent::ValuePropertyComponent(juce::Value const& value, juce::String const& name)
    : PropertyComponent(name), _value(value)
{
    _value.addListener(this);
}

auto ValuePropertyComponent::value() -> juce::Value& { return _value; }

auto ValuePropertyComponent::value() const -> juce::Value const& { return _value; }

auto ValuePropertyComponent::valueChanged(juce::Value&) -> void { refresh(); }

} // namespace mc
