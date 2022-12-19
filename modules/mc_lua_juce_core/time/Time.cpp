#include "Time.hpp"

#include <juce_core/juce_core.h>
namespace mc::lua::bindings {
auto juce_Time(sol::table& state) -> void
{
    auto t = state.new_usertype<juce::Time>("Time", sol::constructors<juce::Time(), juce::Time(juce::int64)>());

    t["toMilliseconds"]                   = &juce::Time::toMilliseconds;
    t["getYear"]                          = &juce::Time::getYear;
    t["getMonth"]                         = &juce::Time::getMonth;
    t["getDayOfMonth"]                    = &juce::Time::getDayOfMonth;
    t["getDayOfWeek"]                     = &juce::Time::getDayOfWeek;
    t["getDayOfYear"]                     = &juce::Time::getDayOfYear;
    t["getHours"]                         = &juce::Time::getHours;
    t["isAfternoon"]                      = &juce::Time::isAfternoon;
    t["getHoursInAmPmFormat"]             = &juce::Time::getHoursInAmPmFormat;
    t["getMinutes"]                       = &juce::Time::getMinutes;
    t["getSeconds"]                       = &juce::Time::getSeconds;
    t["getMilliseconds"]                  = &juce::Time::getMilliseconds;
    t["isDaylightSavingTime"]             = &juce::Time::isDaylightSavingTime;
    t["getTimeZone"]                      = &juce::Time::getTimeZone;
    t["getUTCOffsetSeconds"]              = &juce::Time::getUTCOffsetSeconds;
    t["getUTCOffsetString"]               = &juce::Time::getUTCOffsetString;
    t["toString"]                         = &juce::Time::toString;
    t["formatted"]                        = &juce::Time::formatted;
    t["toISO8601"]                        = &juce::Time::toISO8601;
    t["fromISO8601"]                      = &juce::Time::fromISO8601;
    t["setSystemTimeToThisTime"]          = &juce::Time::setSystemTimeToThisTime;
    t["currentTimeMillis"]                = &juce::Time::currentTimeMillis;
    t["getMillisecondCounter"]            = &juce::Time::getMillisecondCounter;
    t["getMillisecondCounterHiRes"]       = &juce::Time::getMillisecondCounterHiRes;
    t["waitForMillisecondCounter"]        = &juce::Time::waitForMillisecondCounter;
    t["getApproximateMillisecondCounter"] = &juce::Time::getApproximateMillisecondCounter;
    t["getHighResolutionTicks"]           = &juce::Time::getHighResolutionTicks;
    t["getHighResolutionTicksPerSecond"]  = &juce::Time::getHighResolutionTicksPerSecond;
    t["highResolutionTicksToSeconds"]     = &juce::Time::highResolutionTicksToSeconds;
    t["secondsToHighResolutionTicks"]     = &juce::Time::secondsToHighResolutionTicks;
    t["getCompilationDate"]               = &juce::Time::getCompilationDate;

    // t["getMonthName"]                     = &juce::Time::getMonthName;
    // t["getWeekdayName"]                   = &juce::Time::getWeekdayName;
    // t["getWeekdayName"]                   = &juce::Time::getWeekdayName;
    // t["getMonthName"]                     = &juce::Time::getMonthName;
}
} // namespace mc::lua::bindings
