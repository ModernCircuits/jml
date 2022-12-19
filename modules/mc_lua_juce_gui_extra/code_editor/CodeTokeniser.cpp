#include "CodeTokeniser.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc::lua::bindings {

auto juce_CodeTokeniser(sol::table& state) -> void
{
    auto tokeniser                      = state.new_usertype<juce::CodeTokeniser>("InternalCodeTokeniser", sol::no_constructor);
    tokeniser["readNextToken"]          = &juce::CodeTokeniser::readNextToken;
    tokeniser["getDefaultColourScheme"] = &juce::CodeTokeniser::getDefaultColourScheme;
}

} // namespace mc::lua::bindings
