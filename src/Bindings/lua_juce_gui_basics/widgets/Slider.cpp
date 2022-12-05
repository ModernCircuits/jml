#include "Slider.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

SOL_BASE_CLASSES(juce::Slider, juce::MouseListener, juce::Component, juce::TooltipClient, juce::SettableTooltipClient);

auto juce_Slider(sol::table& state) -> void
{

    auto params                 = state.new_usertype<juce::Slider::RotaryParameters>("SliderRotaryParameters");
    params["startAngleRadians"] = &juce::Slider::RotaryParameters::startAngleRadians;
    params["endAngleRadians"]   = &juce::Slider::RotaryParameters::endAngleRadians;
    params["stopAtEnd"]         = &juce::Slider::RotaryParameters::stopAtEnd;

    // clang-format off
    state.new_enum("SliderColourIds",
        "backgroundColourId",
            juce::Slider::ColourIds::backgroundColourId,
        "thumbColourId",
            juce::Slider::ColourIds::thumbColourId,
        "trackColourId",
            juce::Slider::ColourIds::trackColourId,
        "rotarySliderFillColourId",
            juce::Slider::ColourIds::rotarySliderFillColourId,
        "rotarySliderOutlineColourId",
            juce::Slider::ColourIds::rotarySliderOutlineColourId,
        "textBoxBackgroundColourId",
            juce::Slider::ColourIds::textBoxBackgroundColourId,
        "textBoxHighlightColourId",
            juce::Slider::ColourIds::textBoxHighlightColourId,
        "textBoxOutlineColourId",
            juce::Slider::ColourIds::textBoxOutlineColourId,
        "textBoxTextColourId",
            juce::Slider::ColourIds::textBoxTextColourId
    );

    state.new_enum("SliderStyle",
        "LinearHorizontal",
            juce::Slider::SliderStyle::LinearHorizontal,
        "LinearVertical",
            juce::Slider::SliderStyle::LinearVertical,
        "LinearBar",
            juce::Slider::SliderStyle::LinearBar,
        "LinearBarVertical",
            juce::Slider::SliderStyle::LinearBarVertical,
        "Rotary",
            juce::Slider::SliderStyle::Rotary,
        "RotaryHorizontalDrag",
            juce::Slider::SliderStyle::RotaryHorizontalDrag,
        "RotaryVerticalDrag",
            juce::Slider::SliderStyle::RotaryVerticalDrag,
        "RotaryHorizontalVerticalDrag",
            juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        "IncDecButtons",
            juce::Slider::SliderStyle::IncDecButtons,
        "TwoValueHorizontal",
            juce::Slider::SliderStyle::TwoValueHorizontal,
        "TwoValueVertical",
            juce::Slider::SliderStyle::TwoValueVertical,
        "ThreeValueHorizontal",
            juce::Slider::SliderStyle::ThreeValueHorizontal,
        "ThreeValueVertical",
            juce::Slider::SliderStyle::ThreeValueVertical
    );

    state.new_enum("SliderTextEntryBoxPosition",
        "NoTextBox",
            juce::Slider::TextEntryBoxPosition::NoTextBox,
        "TextBoxLeft",
            juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        "TextBoxRight",
            juce::Slider::TextEntryBoxPosition::TextBoxRight,
        "TextBoxAbove",
            juce::Slider::TextEntryBoxPosition::TextBoxAbove,
        "TextBoxBelow",
            juce::Slider::TextEntryBoxPosition::TextBoxBelow
    );

    state.new_enum("SliderDragMode",
        "notDragging",
            juce::Slider::DragMode::notDragging,
        "absoluteDrag",
            juce::Slider::DragMode::absoluteDrag,
        "velocityDrag",
            juce::Slider::DragMode::velocityDrag
    );

    auto slider = state.new_usertype<juce::Slider>("Slider",
        sol::factories(
            [] { return std::make_shared<juce::Slider>(); },
            [](juce::String const& id) { return std::make_shared<juce::Slider>(id); },
            [](juce::Slider::SliderStyle style, juce::Slider::TextEntryBoxPosition pos) { return std::make_shared<juce::Slider>(style, pos); }
        ),
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
    slider["getValue"]                           = &juce::Slider::getValue;
    slider["getValueObject"]                     = &juce::Slider::getValueObject;
    slider["setNormalisableRange"]               = &juce::Slider::setNormalisableRange;
    slider["getRange"]                           = &juce::Slider::getRange;
    slider["getMaximum"]                         = &juce::Slider::getMaximum;
    slider["getMinimum"]                         = &juce::Slider::getMinimum;
    slider["getInterval"]                        = &juce::Slider::getInterval;
    slider["getMinValue"]                        = &juce::Slider::getMinValue;
    slider["getMinValueObject"]                  = &juce::Slider::getMinValueObject;
    slider["getMaxValue"]                        = &juce::Slider::getMaxValue;
    slider["getMaxValueObject"]                  = &juce::Slider::getMaxValueObject;
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

    // slider["setValue"]                           = &juce::Slider::setValue;
    // slider["setMinValue"]                        = &juce::Slider::setMinValue;
    // slider["setMaxValue"]                        = &juce::Slider::setMaxValue;
    // slider["setMinAndMaxValues"]                 = &juce::Slider::setMinAndMaxValues;

    slider["onValueChange"] = &juce::Slider::onValueChange;
    // slider["onDragStart"]           = &juce::Slider::onDragStart;
    // slider["onDragEnd"]             = &juce::Slider::onDragEnd;
    // slider["valueFromTextFunction"] = &juce::Slider::valueFromTextFunction;
    // slider["textFromValueFunction"] = &juce::Slider::textFromValueFunction;
}
