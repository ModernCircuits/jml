#include "Uuid.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_Uuid(sol::table& state) -> void
{
    // clang-format off
    auto uuid = state.new_usertype<juce::Uuid>("Uuid",
        sol::constructors<juce::Uuid(), juce::Uuid(juce::String const&)>()
    );
    // clang-format on
    uuid["isNull"]                 = &juce::Uuid::isNull;
    uuid["toString"]               = &juce::Uuid::toString;
    uuid["toDashedString"]         = &juce::Uuid::toDashedString;
    uuid["getTimeLow"]             = &juce::Uuid::getTimeLow;
    uuid["getTimeMid"]             = &juce::Uuid::getTimeMid;
    uuid["getTimeHighAndVersion"]  = &juce::Uuid::getTimeHighAndVersion;
    uuid["getClockSeqAndReserved"] = &juce::Uuid::getClockSeqAndReserved;
    uuid["getClockSeqLow"]         = &juce::Uuid::getClockSeqLow;
    uuid["getNode"]                = &juce::Uuid::getNode;
    uuid["hash"]                   = &juce::Uuid::hash;
    uuid["getRawData"]             = &juce::Uuid::getRawData;
}
} // namespace mc::lua::bindings
