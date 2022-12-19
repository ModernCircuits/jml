#include "MemoryInputStream.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {

auto juce_MemoryInputStream(sol::table& state) -> void
{
    // clang-format off
    auto stream = state.new_usertype<juce::MemoryInputStream>("MemoryInputStream",
        sol::constructors<
            juce::MemoryInputStream(void const*, size_t, bool),
            juce::MemoryInputStream(juce::MemoryBlock const&, bool)
        >(),
        sol::base_classes, sol::bases<juce::InputStream>()
    );
    // clang-format on

    stream["getData"]     = &juce::MemoryInputStream::getData;
    stream["getDataSize"] = &juce::MemoryInputStream::getDataSize;
}

} // namespace mc::lua::bindings
