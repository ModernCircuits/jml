#include "RelativeTime.hpp"

#include <juce_core/juce_core.h>

auto juce_RelativeTime(sol::table& state) -> void
{
    auto t = state.new_usertype<juce::RelativeTime>("RelativeTime", sol::constructors<juce::RelativeTime(double)>());

    // members
    t["inMilliseconds"]            = &juce::RelativeTime::inMilliseconds;
    t["inSeconds"]                 = &juce::RelativeTime::inSeconds;
    t["inMinutes"]                 = &juce::RelativeTime::inMinutes;
    t["inHours"]                   = &juce::RelativeTime::inHours;
    t["inDays"]                    = &juce::RelativeTime::inDays;
    t["inWeeks"]                   = &juce::RelativeTime::inWeeks;
    t["getDescription"]            = &juce::RelativeTime::getDescription;
    t["getApproximateDescription"] = &juce::RelativeTime::getApproximateDescription;

    // static
    t["milliseconds"] = [](double v) { return juce::RelativeTime::milliseconds(static_cast<juce::int64>(v)); };
    t["seconds"]      = &juce::RelativeTime::seconds;
    t["minutes"]      = &juce::RelativeTime::minutes;
    t["hours"]        = &juce::RelativeTime::hours;
    t["days"]         = &juce::RelativeTime::days;
    t["weeks"]        = &juce::RelativeTime::weeks;
}
