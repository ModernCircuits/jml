#include "Point.hpp"

#include <juce_graphics/juce_graphics.h>

template <typename T>
auto juce_PointImpl(sol::table& state, char const* name) -> void
{
    // TODO(tobi)
    // getPointOnCircumference
    // point["rotatedAboutOrigin"]           = &juce::Point<T>::rotatedAboutOrigin;
    // point["getDotProduct"]                = &juce::Point<T>::getDotProduct;

    auto point = state.new_usertype<juce::Point<T>>(name, sol::constructors<juce::Point<T>(), juce::Point<T>(T, T)>());

    point["isOrigin"]                     = &juce::Point<T>::isOrigin;
    point["isFinite"]                     = &juce::Point<T>::isFinite;
    point["getX"]                         = &juce::Point<T>::getX;
    point["getY"]                         = &juce::Point<T>::getY;
    point["setX"]                         = &juce::Point<T>::setX;
    point["setY"]                         = &juce::Point<T>::setY;
    point["withX"]                        = &juce::Point<T>::withX;
    point["withY"]                        = &juce::Point<T>::withY;
    point["setXY"]                        = &juce::Point<T>::setXY;
    point["addXY"]                        = &juce::Point<T>::addXY;
    point["translated"]                   = &juce::Point<T>::translated;
    point["getDistanceFromOrigin"]        = &juce::Point<T>::getDistanceFromOrigin;
    point["getDistanceFrom"]              = &juce::Point<T>::getDistanceFrom;
    point["getDistanceSquaredFromOrigin"] = &juce::Point<T>::getDistanceSquaredFromOrigin;
    point["getDistanceSquaredFrom"]       = &juce::Point<T>::getDistanceSquaredFrom;
    point["getAngleToPoint"]              = &juce::Point<T>::getAngleToPoint;
    point["applyTransform"]               = &juce::Point<T>::applyTransform;
    point["transformedBy"]                = &juce::Point<T>::transformedBy;
    point["toInt"]                        = &juce::Point<T>::toInt;
    point["toFloat"]                      = &juce::Point<T>::toFloat;
    point["toDouble"]                     = &juce::Point<T>::toDouble;
    point["roundToInt"]                   = &juce::Point<T>::roundToInt;
    point["toString"]                     = &juce::Point<T>::toString;
}

auto juce_Point(sol::table& state) -> void
{
    juce_PointImpl<int>(state, "PointInt");
    juce_PointImpl<float>(state, "PointFloat");
    juce_PointImpl<double>(state, "PointDouble");
}