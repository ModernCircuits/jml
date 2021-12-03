#include "Slider.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_Slider(sol::table& state) -> void
{
    auto params                 = state.new_usertype<juce::Slider::RotaryParameters>("SliderRotaryParameters");
    params["startAngleRadians"] = &juce::Slider::RotaryParameters::startAngleRadians;
    params["endAngleRadians"]   = &juce::Slider::RotaryParameters::endAngleRadians;
    params["stopAtEnd"]         = &juce::Slider::RotaryParameters::stopAtEnd;

    // clang-format off
    auto slider = state.new_usertype<juce::Slider>("Slider",
        sol::constructors<
            juce::Slider(),
            juce::Slider(juce::String const&),
            juce::Slider(juce::Slider::SliderStyle, juce::Slider::TextEntryBoxPosition)
        >(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    slider.set_function("setRange", sol::overload(
            static_cast<void (juce::Slider::*)(juce::Range<double>, double)>(&juce::Slider::setRange),
            static_cast<void (juce::Slider::*)(double, double, double)>(&juce::Slider::setRange),
            [] (juce::Slider* slider, double minValue, double maxValue) { slider->setRange(minValue, maxValue); }
        )
    );
    slider.set_function("setRotaryParameters", sol::overload(
            static_cast<void (juce::Slider::*)(juce::Slider::RotaryParameters)>(&juce::Slider::setRotaryParameters),
            static_cast<void (juce::Slider::*)(float, float, bool)>(&juce::Slider::setRotaryParameters)
        )
    );
    // clang-format on

    slider["setSliderStyle"]                     = &juce::Slider::setSliderStyle;
    slider["getSliderStyle"]                     = &juce::Slider::getSliderStyle;
    slider["getRotaryParameters"]                = &juce::Slider::getRotaryParameters;
    slider["setMouseDragSensitivity"]            = &juce::Slider::setMouseDragSensitivity;
    slider["getMouseDragSensitivity"]            = &juce::Slider::getMouseDragSensitivity;
    slider["setVelocityBasedMode"]               = &juce::Slider::setVelocityBasedMode;
    slider["getVelocityBasedMode"]               = &juce::Slider::getVelocityBasedMode;
    slider["setVelocityModeParameters"]          = &juce::Slider::setVelocityModeParameters;
    slider["getVelocitySensitivity"]             = &juce::Slider::getVelocitySensitivity;
    slider["getVelocityThreshold"]               = &juce::Slider::getVelocityThreshold;
    slider["getVelocityOffset"]                  = &juce::Slider::getVelocityOffset;
    slider["getVelocityModeIsSwappable"]         = &juce::Slider::getVelocityModeIsSwappable;
    slider["setSkewFactor"]                      = &juce::Slider::setSkewFactor;
    slider["setSkewFactorFromMidPoint"]          = &juce::Slider::setSkewFactorFromMidPoint;
    slider["getSkewFactor"]                      = &juce::Slider::getSkewFactor;
    slider["isSymmetricSkew"]                    = &juce::Slider::isSymmetricSkew;
    slider["setIncDecButtonsMode"]               = &juce::Slider::setIncDecButtonsMode;
    slider["setTextBoxStyle"]                    = &juce::Slider::setTextBoxStyle;
    slider["getTextBoxPosition"]                 = &juce::Slider::getTextBoxPosition;
    slider["getTextBoxWidth"]                    = &juce::Slider::getTextBoxWidth;
    slider["getTextBoxHeight"]                   = &juce::Slider::getTextBoxHeight;
    slider["setTextBoxIsEditable"]               = &juce::Slider::setTextBoxIsEditable;
    slider["isTextBoxEditable"]                  = &juce::Slider::isTextBoxEditable;
    slider["showTextBox"]                        = &juce::Slider::showTextBox;
    slider["hideTextBox"]                        = &juce::Slider::hideTextBox;
    // slider["setValue"]                           = &juce::Slider::setValue;
    slider["getValue"]                           = &juce::Slider::getValue;
    slider["getValueObject"]                     = &juce::Slider::getValueObject;
    slider["setNormalisableRange"]               = &juce::Slider::setNormalisableRange;
    slider["getRange"]                           = &juce::Slider::getRange;
    slider["getMaximum"]                         = &juce::Slider::getMaximum;
    slider["getMinimum"]                         = &juce::Slider::getMinimum;
    slider["getInterval"]                        = &juce::Slider::getInterval;
    slider["getMinValue"]                        = &juce::Slider::getMinValue;
    slider["getMinValueObject"]                  = &juce::Slider::getMinValueObject;
    // slider["setMinValue"]                        = &juce::Slider::setMinValue;
    slider["getMaxValue"]                        = &juce::Slider::getMaxValue;
    slider["getMaxValueObject"]                  = &juce::Slider::getMaxValueObject;
    // slider["setMaxValue"]                        = &juce::Slider::setMaxValue;
    // slider["setMinAndMaxValues"]                 = &juce::Slider::setMinAndMaxValues;
    slider["addListener"]                        = &juce::Slider::addListener;
    slider["removeListener"]                     = &juce::Slider::removeListener;
    slider["setDoubleClickReturnValue"]          = &juce::Slider::setDoubleClickReturnValue;
    slider["getDoubleClickReturnValue"]          = &juce::Slider::getDoubleClickReturnValue;
    slider["isDoubleClickReturnEnabled"]         = &juce::Slider::isDoubleClickReturnEnabled;
    slider["setChangeNotificationOnlyOnRelease"] = &juce::Slider::setChangeNotificationOnlyOnRelease;
    slider["setSliderSnapsToMousePosition"]      = &juce::Slider::setSliderSnapsToMousePosition;
    slider["getSliderSnapsToMousePosition"]      = &juce::Slider::getSliderSnapsToMousePosition;
    slider["setPopupDisplayEnabled"]             = &juce::Slider::setPopupDisplayEnabled;
    slider["getCurrentPopupDisplay"]             = &juce::Slider::getCurrentPopupDisplay;
    slider["setPopupMenuEnabled"]                = &juce::Slider::setPopupMenuEnabled;
    slider["setScrollWheelEnabled"]              = &juce::Slider::setScrollWheelEnabled;
    slider["isScrollWheelEnabled"]               = &juce::Slider::isScrollWheelEnabled;
    slider["getThumbBeingDragged"]               = &juce::Slider::getThumbBeingDragged;
    slider["startedDragging"]                    = &juce::Slider::startedDragging;
    slider["stoppedDragging"]                    = &juce::Slider::stoppedDragging;
    slider["valueChanged"]                       = &juce::Slider::valueChanged;
    slider["getValueFromText"]                   = &juce::Slider::getValueFromText;
    slider["getTextFromValue"]                   = &juce::Slider::getTextFromValue;
    slider["setTextValueSuffix"]                 = &juce::Slider::setTextValueSuffix;
    slider["getTextValueSuffix"]                 = &juce::Slider::getTextValueSuffix;
    slider["getNumDecimalPlacesToDisplay"]       = &juce::Slider::getNumDecimalPlacesToDisplay;
    slider["setNumDecimalPlacesToDisplay"]       = &juce::Slider::setNumDecimalPlacesToDisplay;
    slider["proportionOfLengthToValue"]          = &juce::Slider::proportionOfLengthToValue;
    slider["valueToProportionOfLength"]          = &juce::Slider::valueToProportionOfLength;
    slider["getPositionOfValue"]                 = &juce::Slider::getPositionOfValue;
    slider["snapValue"]                          = &juce::Slider::snapValue;
    slider["updateText"]                         = &juce::Slider::updateText;
    slider["isHorizontal"]                       = &juce::Slider::isHorizontal;
    slider["isVertical"]                         = &juce::Slider::isVertical;
    slider["isRotary"]                           = &juce::Slider::isRotary;
    slider["isBar"]                              = &juce::Slider::isBar;
    slider["isTwoValue"]                         = &juce::Slider::isTwoValue;

    //slider["onValueChange"]         = &juce::Slider::onValueChange;
    //slider["onDragStart"]           = &juce::Slider::onDragStart;
    //slider["onDragEnd"]             = &juce::Slider::onDragEnd;
    //slider["valueFromTextFunction"] = &juce::Slider::valueFromTextFunction;
    //slider["textFromValueFunction"] = &juce::Slider::textFromValueFunction;
}
