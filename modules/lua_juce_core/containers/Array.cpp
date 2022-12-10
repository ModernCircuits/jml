#include "Array.hpp"

auto juce_Array(sol::table& state) -> void
{
    juce_ArrayImpl<int>(state, "Array_int");
    juce_ArrayImpl<float>(state, "Array_float");
    juce_ArrayImpl<double>(state, "Array_double");

    juce_ArrayImpl<juce::String>(state, "Array_String"); // StringArray is a separate type.
    juce_ArrayImpl<juce::File>(state, "Array_File");
    juce_ArrayImpl<juce::var>(state, "Array_var");
}
