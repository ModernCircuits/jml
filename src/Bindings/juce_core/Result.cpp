#include "Result.hpp"

#include <juce_core/juce_core.h>

auto juce_Result(sol::table& state) -> void
{
    auto result               = state.new_usertype<juce::Result>("Result");
    result["wasOk"]           = &juce::Result::wasOk;
    result["failed"]          = &juce::Result::failed;
    result["getErrorMessage"] = &juce::Result::getErrorMessage;
    result["ok"]              = &juce::Result::ok;
    result["fail"]            = &juce::Result::fail;
}
