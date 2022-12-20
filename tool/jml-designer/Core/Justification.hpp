#pragma once

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {
[[nodiscard]] auto makeJustificationProperty(juce::Value value, juce::String const& name)
    -> UniquePtr<juce::PropertyComponent>;
}

template<>
struct juce::VariantConverter<juce::Justification>
{
    [[nodiscard]] static auto toVar(juce::Justification const& justification) -> juce::var;
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Justification;
};
