#include "Property/ValuePropertyComponent.hpp"

#include <utility>

namespace mc {

ValuePropertyComponent::ValuePropertyComponent(juce::Value value, juce::String const& name)
    : PropertyComponent(name), _value(std::move(value))
{
    _value.addListener(this);
}

auto ValuePropertyComponent::value() -> juce::Value& { return _value; }

auto ValuePropertyComponent::value() const -> juce::Value const& { return _value; }

auto ValuePropertyComponent::valueChanged(juce::Value& /*value*/) -> void { refresh(); }

} // namespace mc
