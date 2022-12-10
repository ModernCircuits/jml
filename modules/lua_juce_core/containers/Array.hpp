#pragma once

template<typename T>
auto juce_ArrayImpl(sol::table& state, char const* name) -> void
{
    auto noOperators                           = sol::automagic_enrollments{};
    noOperators.less_than_operator             = false;
    noOperators.less_than_or_equal_to_operator = false;
    noOperators.equal_to_operator              = false;

    auto array = state.new_usertype<juce::Array<T>>(name, noOperators);

    array["clear"]                    = &juce::Array<T>::clear;
    array["clearQuick"]               = &juce::Array<T>::clearQuick;
    array["fill"]                     = &juce::Array<T>::fill;
    array["size"]                     = &juce::Array<T>::size;
    array["isEmpty"]                  = &juce::Array<T>::isEmpty;
    array["getUnchecked"]             = &juce::Array<T>::getUnchecked;
    array["getFirst"]                 = &juce::Array<T>::getFirst;
    array["getLast"]                  = &juce::Array<T>::getLast;
    array["insert"]                   = &juce::Array<T>::insert;
    array["insertMultiple"]           = &juce::Array<T>::insertMultiple;
    array["set"]                      = &juce::Array<T>::set;
    array["setUnchecked"]             = &juce::Array<T>::setUnchecked;
    array["resize"]                   = &juce::Array<T>::resize;
    array["removeAndReturn"]          = &juce::Array<T>::removeAndReturn;
    array["removeRange"]              = &juce::Array<T>::removeRange;
    array["removeLast"]               = &juce::Array<T>::removeLast;
    array["swap"]                     = &juce::Array<T>::swap;
    array["move"]                     = &juce::Array<T>::move;
    array["minimiseStorageOverheads"] = &juce::Array<T>::minimiseStorageOverheads;
    array["ensureStorageAllocated"]   = &juce::Array<T>::ensureStorageAllocated;
    array["add"]                      = [](juce::Array<T>* array, T const& t) { array->add(t); };

    // array["indexOf"]                  = &juce::Array<T>::indexOf;
    // array["contains"]                 = &juce::Array<T>::contains;
    // array["addIfNotAlreadyThere"]     = &juce::Array<T>::addIfNotAlreadyThere;
    // array["swapWith"]                 = &juce::Array<T>::swapWith;
    // array["addSorted"]                = &juce::Array<T>::addSorted;
    // array["addUsingDefaultSort"]      = &juce::Array<T>::addUsingDefaultSort;
    // array["indexOfSorted"]            = &juce::Array<T>::indexOfSorted;
    // array["removeFirstMatchingValue"] = &juce::Array<T>::removeFirstMatchingValue;
    // array["removeAllInstancesOf"]     = &juce::Array<T>::removeAllInstancesOf;
    // array["removeIf"]                 = &juce::Array<T>::removeIf;
    // array["removeValuesIn"]           = &juce::Array<T>::removeValuesIn;
    // array["removeValuesNotIn"]        = &juce::Array<T>::removeValuesNotIn;

    // TODO(tobi)
    // getReference
    // getRawDataPointer
    // begin
    // end
    // data
    // add
    // insertArray
    // addArray
    // addNullTerminatedArray
    // remove
    // sort
    // getLock
}

auto juce_Array(sol::table& state) -> void;
