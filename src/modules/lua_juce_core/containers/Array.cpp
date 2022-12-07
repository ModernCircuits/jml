#include "Array.hpp"

auto juce_Array(sol::table& state) -> void
{
    juce_ArrayImpl<int>(state, "IntArray");
    juce_ArrayImpl<float>(state, "FloatArray");
    juce_ArrayImpl<double>(state, "DoubleArray");

    juce_ArrayImpl<juce::String>(state, "InternalStringArray"); // StringArray is a separate type.
    juce_ArrayImpl<juce::File>(state, "FileArray");
    juce_ArrayImpl<juce::var>(state, "VarArray");
}
