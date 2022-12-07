#include "StringArray.hpp"

auto juce_StringArray(sol::table& state) -> void
{
    auto array = state.new_usertype<juce::StringArray>("StringArray", sol::constructors<juce::StringArray()>());

    array["size"]                      = &juce::StringArray::size;
    array["isEmpty"]                   = &juce::StringArray::isEmpty;
    array["swapWith"]                  = &juce::StringArray::swapWith;
    array["contains"]                  = &juce::StringArray::contains;
    array["indexOf"]                   = &juce::StringArray::indexOf;
    array["add"]                       = &juce::StringArray::add;
    array["mergeArray"]                = &juce::StringArray::mergeArray;
    array["addLines"]                  = &juce::StringArray::addLines;
    array["clear"]                     = &juce::StringArray::clear;
    array["clearQuick"]                = &juce::StringArray::clearQuick;
    array["remove"]                    = &juce::StringArray::remove;
    array["removeString"]              = &juce::StringArray::removeString;
    array["removeRange"]               = &juce::StringArray::removeRange;
    array["removeDuplicates"]          = &juce::StringArray::removeDuplicates;
    array["removeEmptyStrings"]        = &juce::StringArray::removeEmptyStrings;
    array["move"]                      = &juce::StringArray::move;
    array["trim"]                      = &juce::StringArray::trim;
    array["appendNumbersToDuplicates"] = &juce::StringArray::appendNumbersToDuplicates;
    array["joinIntoString"]            = &juce::StringArray::joinIntoString;
    // array["sort"]                      = &juce::StringArray::sort;
    // array["sortNatural"]               = &juce::StringArray::sortNatural;
    array["minimiseStorageOverheads"] = &juce::StringArray::minimiseStorageOverheads;
    array["ensureStorageAllocated"]   = &juce::StringArray::ensureStorageAllocated;
    // array["fromLines"]                 = &juce::StringArray::fromLines;
    // array["strings"]                   = &juce::StringArray::strings;

    // TODO(tobi)
    // getReference
    // begin
    // end
    // addTokens
    // fromTokens
}
