#include "StatisticsAccumulator.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
template<typename T>
auto juce_StatisticsAccumulatorImpl(sol::table& state, char const* name) -> void
{
    using Accumulator            = juce::StatisticsAccumulator<T>;
    auto type                    = state.new_usertype<Accumulator>(name, sol::constructors<Accumulator()>());
    type["getAverage"]           = &Accumulator::getAverage;
    type["getVariance"]          = &Accumulator::getVariance;
    type["getStandardDeviation"] = &Accumulator::getStandardDeviation;
    type["getMinValue"]          = &Accumulator::getMinValue;
    type["getMaxValue"]          = &Accumulator::getMaxValue;
    type["getCount"]             = &Accumulator::getCount;
}

auto juce_StatisticsAccumulator(sol::table& state) -> void
{
    juce_StatisticsAccumulatorImpl<float>(state, "StatisticsAccumulatorFloat");
    juce_StatisticsAccumulatorImpl<double>(state, "StatisticsAccumulatorDouble");
}
} // namespace mc::lua::bindings
