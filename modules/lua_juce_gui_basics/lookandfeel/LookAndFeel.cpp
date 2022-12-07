#include "LookAndFeel.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_LookAndFeel(sol::table& state) -> void
{
    auto lnf = state.new_usertype<juce::LookAndFeel>("LookAndFeel", sol::meta_function::construct, sol::no_constructor);

    lnf["findColour"]                      = &juce::LookAndFeel::findColour;
    lnf["setColour"]                       = &juce::LookAndFeel::setColour;
    lnf["isColourSpecified"]               = &juce::LookAndFeel::isColourSpecified;
    lnf["setDefaultSansSerifTypeface"]     = &juce::LookAndFeel::setDefaultSansSerifTypeface;
    lnf["setDefaultSansSerifTypefaceName"] = &juce::LookAndFeel::setDefaultSansSerifTypefaceName;
    lnf["getMouseCursorFor"]               = &juce::LookAndFeel::getMouseCursorFor;
    lnf["createGraphicsContext"]           = &juce::LookAndFeel::createGraphicsContext;
    lnf["setUsingNativeAlertWindows"]      = &juce::LookAndFeel::setUsingNativeAlertWindows;
    lnf["isUsingNativeAlertWindows"]       = &juce::LookAndFeel::isUsingNativeAlertWindows;
    lnf["drawSpinningWaitAnimation"]       = &juce::LookAndFeel::drawSpinningWaitAnimation;
    lnf["getTickShape"]                    = &juce::LookAndFeel::getTickShape;
    lnf["getCrossShape"]                   = &juce::LookAndFeel::getCrossShape;
    lnf["createDropShadowerForComponent"]  = &juce::LookAndFeel::createDropShadowerForComponent;
    lnf["playAlertSound"]                  = &juce::LookAndFeel::playAlertSound;
    // lnf["getTypefaceForFont"]           = &juce::LookAndFeel::getTypefaceForFont;
}
