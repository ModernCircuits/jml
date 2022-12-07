#pragma once

template<typename T>
auto juce_ArrayImpl(sol::table& state, char const* name) -> void
{
    auto array = state.new_usertype<juce::Array<T>>(name, sol::constructors<juce::Array<T>()>());

    array["clear"]                = &juce::Array<T>::clear;
    array["clearQuick"]           = &juce::Array<T>::clearQuick;
    array["fill"]                 = &juce::Array<T>::fill;
    array["size"]                 = &juce::Array<T>::size;
    array["isEmpty"]              = &juce::Array<T>::isEmpty;
    array["getUnchecked"]         = &juce::Array<T>::getUnchecked;
    array["getFirst"]             = &juce::Array<T>::getFirst;
    array["getLast"]              = &juce::Array<T>::getLast;
    array["indexOf"]              = &juce::Array<T>::indexOf;
    array["contains"]             = &juce::Array<T>::contains;
    array["insert"]               = &juce::Array<T>::insert;
    array["insertMultiple"]       = &juce::Array<T>::insertMultiple;
    array["addIfNotAlreadyThere"] = &juce::Array<T>::addIfNotAlreadyThere;
    array["set"]                  = &juce::Array<T>::set;
    array["setUnchecked"]         = &juce::Array<T>::setUnchecked;
    // array["swapWith"]                 = &juce::Array<T>::swapWith;
    array["resize"] = &juce::Array<T>::resize;
    // array["addSorted"]                = &juce::Array<T>::addSorted;
    array["addUsingDefaultSort"] = &juce::Array<T>::addUsingDefaultSort;
    // array["indexOfSorted"]            = &juce::Array<T>::indexOfSorted;
    array["removeAndReturn"]          = &juce::Array<T>::removeAndReturn;
    array["removeFirstMatchingValue"] = &juce::Array<T>::removeFirstMatchingValue;
    array["removeAllInstancesOf"]     = &juce::Array<T>::removeAllInstancesOf;
    // array["removeIf"]                 = &juce::Array<T>::removeIf;
    array["removeRange"] = &juce::Array<T>::removeRange;
    array["removeLast"]  = &juce::Array<T>::removeLast;
    // array["removeValuesIn"]           = &juce::Array<T>::removeValuesIn;
    // array["removeValuesNotIn"]        = &juce::Array<T>::removeValuesNotIn;
    array["swap"]                     = &juce::Array<T>::swap;
    array["move"]                     = &juce::Array<T>::move;
    array["minimiseStorageOverheads"] = &juce::Array<T>::minimiseStorageOverheads;
    array["ensureStorageAllocated"]   = &juce::Array<T>::ensureStorageAllocated;

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
