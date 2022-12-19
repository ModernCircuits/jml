#include "MemoryBlock.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_MemoryBlock(sol::table& state) -> void
{
    // clang-format off
    auto mb = state.new_usertype<juce::MemoryBlock>("MemoryBlock",
        sol::constructors<
            juce::MemoryBlock(),
            juce::MemoryBlock(size_t, bool),
            juce::MemoryBlock(void const*, size_t)
        >()
    );
    // clang-format on

    mb["matches"]            = &juce::MemoryBlock::matches;
    mb["isEmpty"]            = &juce::MemoryBlock::isEmpty;
    mb["getSize"]            = &juce::MemoryBlock::getSize;
    mb["setSize"]            = &juce::MemoryBlock::setSize;
    mb["ensureSize"]         = &juce::MemoryBlock::ensureSize;
    mb["reset"]              = &juce::MemoryBlock::reset;
    mb["fillWith"]           = &juce::MemoryBlock::fillWith;
    mb["append"]             = &juce::MemoryBlock::append;
    mb["replaceAll"]         = &juce::MemoryBlock::replaceAll;
    mb["insert"]             = &juce::MemoryBlock::insert;
    mb["removeSection"]      = &juce::MemoryBlock::removeSection;
    mb["copyFrom"]           = &juce::MemoryBlock::copyFrom;
    mb["copyTo"]             = &juce::MemoryBlock::copyTo;
    mb["swapWith"]           = &juce::MemoryBlock::swapWith;
    mb["toString"]           = &juce::MemoryBlock::toString;
    mb["loadFromHexString"]  = &juce::MemoryBlock::loadFromHexString;
    mb["setBitRange"]        = &juce::MemoryBlock::setBitRange;
    mb["getBitRange"]        = &juce::MemoryBlock::getBitRange;
    mb["toBase64Encoding"]   = &juce::MemoryBlock::toBase64Encoding;
    mb["fromBase64Encoding"] = &juce::MemoryBlock::fromBase64Encoding;
}
} // namespace mc::lua::bindings
