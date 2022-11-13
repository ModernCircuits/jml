#include "Timer.hpp"

#include <juce_events/juce_events.h>

auto juce_Timer(sol::table& state) -> void
{
    auto timer = state.new_usertype<juce::Timer>("InternalTimer", sol::meta_function::construct, sol::no_constructor);

    timer["timerCallback"]                  = &juce::Timer::timerCallback;
    timer["startTimer"]                     = &juce::Timer::startTimer;
    timer["startTimerHz"]                   = &juce::Timer::startTimerHz;
    timer["stopTimer"]                      = &juce::Timer::stopTimer;
    timer["isTimerRunning"]                 = &juce::Timer::isTimerRunning;
    timer["getTimerInterval"]               = &juce::Timer::getTimerInterval;
    timer["callAfterDelay"]                 = &juce::Timer::callAfterDelay;
    timer["callPendingTimersSynchronously"] = &juce::Timer::callPendingTimersSynchronously;
}