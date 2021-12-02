#include "Range.hpp"

#include <juce_core/juce_core.h>

template <typename T>
auto juce_RangeImpl(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto range = state.new_usertype<juce::Range<T>>(name,
        sol::constructors<juce::Range<T>(), juce::Range<T>(T, T)>(),
        "start",
        sol::property(&juce::Range<T>::getStart, &juce::Range<T>::setStart),
        "end",
        sol::property(&juce::Range<T>::getEnd, &juce::Range<T>::setEnd)
    );
    // clang-format on
}

auto juce_Range(sol::table& state) -> void
{
    juce_RangeImpl<int>(state, "RangeInt");
    juce_RangeImpl<juce::int64>(state, "RangeInt64");

    juce_RangeImpl<float>(state, "RangeFloat");
    juce_RangeImpl<double>(state, "RangeDouble");
}