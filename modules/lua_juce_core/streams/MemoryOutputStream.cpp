#include "MemoryOutputStream.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {

auto juce_MemoryOutputStream(sol::table& state) -> void
{
    // clang-format off
    auto stream = state.new_usertype<juce::MemoryOutputStream>("MemoryOutputStream",
        sol::constructors<
            juce::MemoryOutputStream(size_t),
            juce::MemoryOutputStream(juce::MemoryBlock&, bool),
            juce::MemoryOutputStream(void*, size_t)
        >(),
        sol::base_classes, sol::bases<juce::OutputStream>()
    );
    // clang-format on

    stream["getData"]        = &juce::MemoryOutputStream::getData;
    stream["getDataSize"]    = &juce::MemoryOutputStream::getDataSize;
    stream["reset"]          = &juce::MemoryOutputStream::reset;
    stream["preallocate"]    = &juce::MemoryOutputStream::preallocate;
    stream["appendUTF8Char"] = &juce::MemoryOutputStream::appendUTF8Char;
    stream["toUTF8"]         = &juce::MemoryOutputStream::toUTF8;
    stream["toString"]       = &juce::MemoryOutputStream::toString;
    stream["getMemoryBlock"] = &juce::MemoryOutputStream::getMemoryBlock;
}

} // namespace mc::lua::bindings
