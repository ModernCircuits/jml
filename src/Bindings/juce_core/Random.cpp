#include "Random.hpp"

#include <juce_core/juce_core.h>

auto juce_Random(sol::table& state) -> void
{
    // clang-format off
    auto rand = state.new_usertype<juce::Random>("Random");
    rand.set_function("getSystemRandom", &juce::Random::getSystemRandom);
    rand.set_function("setSeed", &juce::Random::setSeed);
    rand.set_function("getSeed", &juce::Random::getSeed);
    rand.set_function("nextBool", &juce::Random::nextBool);
    rand.set_function("nextFloat", &juce::Random::nextFloat);
    rand.set_function("nextDouble", &juce::Random::nextDouble);
    rand.set_function("nextInt64", &juce::Random::nextInt64);
    rand.set_function("nextInt", sol::overload(
            static_cast<int (juce::Random::*)() noexcept>(&juce::Random::nextInt),
            static_cast<int (juce::Random::*)(int) noexcept>(&juce::Random::nextInt),
            static_cast<int (juce::Random::*)(juce::Range<int>) noexcept>(&juce::Random::nextInt)
        )
    );
    // clang-format on
}