#include "NormalisableRange.hpp"

#include <juce_core/juce_core.h>

template <typename T>
auto juce_NormalisableRangeImpl(sol::table& state, char const* name) -> void
{
    using Range = juce::NormalisableRange<T>;
    // clang-format off
    auto range = state.new_usertype<Range>(name,
        sol::constructors<
            Range(),
            Range(T, T, T, T, bool),
            Range(T, T, T),
            Range(juce::Range<T>),
            Range(juce::Range<T>, T),
            Range(T, T, Range::ValueRemapFunction, Range::ValueRemapFunction, Range::ValueRemapFunction)
        >()
    );
    // clang-format on

    range["convertTo0to1"]    = &Range::convertTo0to1;
    range["convertFrom0to1"]  = &Range::convertFrom0to1;
    range["snapToLegalValue"] = &Range::snapToLegalValue;
    range["getRange"]         = &Range::getRange;
    range["setSkewForCentre"] = &Range::setSkewForCentre;

    range["start"]         = &Range::start;
    range["end"]           = &Range::end;
    range["interval"]      = &Range::interval;
    range["skew"]          = &Range::skew;
    range["symmetricSkew"] = &Range::symmetricSkew;
}

auto juce_NormalisableRange(sol::table& state) -> void
{
    juce_NormalisableRangeImpl<float>(state, "NormalisableRangeFloat");
    juce_NormalisableRangeImpl<double>(state, "NormalisableRangeDouble");
}