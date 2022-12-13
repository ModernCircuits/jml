#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct ValuePropertyComponent
    : juce::PropertyComponent
    , private juce::Value::Listener
{

    ValuePropertyComponent(juce::Value value, juce::String const& name);
    ~ValuePropertyComponent() override = default;

    [[nodiscard]] auto value() -> juce::Value&;
    [[nodiscard]] auto value() const -> juce::Value const&;

private:
    auto valueChanged(juce::Value& /*value*/) -> void override;

    juce::Value _value;
};

} // namespace mc
