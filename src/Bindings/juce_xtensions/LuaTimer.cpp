#include "LuaTimer.hpp"

#include <juce_events/juce_events.h>

struct LuaTimer final : juce::Timer {
    sol::function lua_timerCallback;

    LuaTimer()           = default;
    ~LuaTimer() override = default;

    auto timerCallback() -> void override
    {
        if (lua_timerCallback.valid()) { lua_timerCallback(std::ref(*this)); }
    }
};

auto juce_LuaTimer(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<LuaTimer>("LuaTimer",
	    sol::constructors<LuaTimer()>(),
        sol::base_classes, sol::bases<juce::Timer>(),
        "timerCallback",
	    &LuaTimer::lua_timerCallback
    );
    // clang-format on
}