#include "PerformanceCounter.hpp"

namespace mc::lua::bindings {
auto juce_PerformanceCounter(sol::table& state) -> void
{
    // clang-format off
    auto pc = state.new_usertype<juce::PerformanceCounter>(
        "PerformanceCounter",
        sol::constructors<juce::PerformanceCounter(juce::String const&, int, juce::File const&)>()
    );
    // clang-format on

    pc["start"]                 = &juce::PerformanceCounter::start;
    pc["stop"]                  = &juce::PerformanceCounter::stop;
    pc["printStatistics"]       = &juce::PerformanceCounter::printStatistics;
    pc["getStatisticsAndReset"] = &juce::PerformanceCounter::getStatisticsAndReset;
}
} // namespace mc::lua::bindings
