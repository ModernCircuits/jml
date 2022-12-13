#pragma once

#include <mc_data_structures/mc_data_structures.hpp>

namespace mc {

template<typename T>
[[nodiscard]] auto toVar(T const& v) -> juce::var
{
    return juce::VariantConverter<T>::toVar(v);
}

template<typename T>
[[nodiscard]] auto fromVar(juce::var const& v) -> T
{
    return juce::VariantConverter<T>::fromVar(v);
}

template<typename T>
[[nodiscard]] auto fromVar(juce::Value const& v) -> T
{
    return fromVar<T>(v.getValue());
}

[[nodiscard]] auto loadValueTree(juce::File const& file, bool asXml) -> juce::ValueTree;
auto saveValueTree(juce::ValueTree const& v, juce::File const& file, bool asXml) -> bool;

} // namespace mc
