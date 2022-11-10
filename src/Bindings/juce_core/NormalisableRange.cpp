#include "NormalisableRange.hpp"

#include <juce_core/juce_core.h>

template <typename T>
auto juce_NormalisableRangeImpl(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto range = state.new_usertype<juce::NormalisableRange<T>>(name,
        sol::constructors<
            juce::NormalisableRange<T>(),
            juce::NormalisableRange<T>(T, T, T, T, bool),
            juce::NormalisableRange<T>(T, T, T),
            juce::NormalisableRange<T>(juce::Range<T>),
            juce::NormalisableRange<T>(juce::Range<T>, T)
            // juce::NormalisableRange<T>(T, T, juce::NormalisableRange<T>::ValueRemapFunction, juce::NormalisableRange<T>::ValueRemapFunction, juce::NormalisableRange<T>::ValueRemapFunction)
        >()
    );
    // clang-format on

    range["convertTo0to1"]    = &juce::NormalisableRange<T>::convertTo0to1;
    range["convertFrom0to1"]  = &juce::NormalisableRange<T>::convertFrom0to1;
    range["snapToLegalValue"] = &juce::NormalisableRange<T>::snapToLegalValue;
    range["getRange"]         = &juce::NormalisableRange<T>::getRange;
    range["setSkewForCentre"] = &juce::NormalisableRange<T>::setSkewForCentre;

    range["start"]         = &juce::NormalisableRange<T>::start;
    range["end"]           = &juce::NormalisableRange<T>::end;
    range["interval"]      = &juce::NormalisableRange<T>::interval;
    range["skew"]          = &juce::NormalisableRange<T>::skew;
    range["symmetricSkew"] = &juce::NormalisableRange<T>::symmetricSkew;
}

auto juce_NormalisableRange(sol::table& state) -> void
{
    juce_NormalisableRangeImpl<float>(state, "NormalisableRangeFloat");
    juce_NormalisableRangeImpl<double>(state, "NormalisableRangeDouble");
}