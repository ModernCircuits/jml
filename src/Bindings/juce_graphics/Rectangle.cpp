#include "Rectangle.hpp"

#include <juce_graphics/juce_graphics.h>

template <typename T>
auto juce_RectangleImpl(sol::table& state, char const* name) -> void
{
    // TODO(tobi)
    // setPosition
    // setCentre
    // withPosition
    // expanded
    // contains
    // intersects
    // intersectRectangle
    // rect["intersectRectangles"]      = &juce::Rectangle<T>::intersectRectangles;

    // clang-format off
    auto rect = state.new_usertype<juce::Rectangle<T>>(name,
        sol::constructors<
            juce::Rectangle<T>(),
            juce::Rectangle<T>(T, T, T, T)
        >()
    );
    rect["reduced"] = sol::overload(
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T) const noexcept>(&juce::Rectangle<T>::reduced),
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T, T) const noexcept>(&juce::Rectangle<T>::reduced)
    );
    // clang-format on

    rect["isEmpty"]                     = &juce::Rectangle<T>::isEmpty;
    rect["isFinite"]                    = &juce::Rectangle<T>::isFinite;
    rect["getX"]                        = &juce::Rectangle<T>::getX;
    rect["getY"]                        = &juce::Rectangle<T>::getY;
    rect["getWidth"]                    = &juce::Rectangle<T>::getWidth;
    rect["getHeight"]                   = &juce::Rectangle<T>::getHeight;
    rect["getRight"]                    = &juce::Rectangle<T>::getRight;
    rect["getBottom"]                   = &juce::Rectangle<T>::getBottom;
    rect["getCentreX"]                  = &juce::Rectangle<T>::getCentreX;
    rect["getCentreY"]                  = &juce::Rectangle<T>::getCentreY;
    rect["getCentre"]                   = &juce::Rectangle<T>::getCentre;
    rect["getAspectRatio"]              = &juce::Rectangle<T>::getAspectRatio;
    rect["getPosition"]                 = &juce::Rectangle<T>::getPosition;
    rect["getBottom"]                   = &juce::Rectangle<T>::getBottom;
    rect["getTopLeft"]                  = &juce::Rectangle<T>::getTopLeft;
    rect["getTopRight"]                 = &juce::Rectangle<T>::getTopRight;
    rect["getBottomLeft"]               = &juce::Rectangle<T>::getBottomLeft;
    rect["getBottomRight"]              = &juce::Rectangle<T>::getBottomRight;
    rect["getHorizontalRange"]          = &juce::Rectangle<T>::getHorizontalRange;
    rect["getVerticalRange"]            = &juce::Rectangle<T>::getVerticalRange;
    rect["setSize"]                     = &juce::Rectangle<T>::setSize;
    rect["setBounds"]                   = &juce::Rectangle<T>::setBounds;
    rect["setX"]                        = &juce::Rectangle<T>::setX;
    rect["setY"]                        = &juce::Rectangle<T>::setY;
    rect["setWidth"]                    = &juce::Rectangle<T>::setWidth;
    rect["setHeight"]                   = &juce::Rectangle<T>::setHeight;
    rect["setHorizontalRange"]          = &juce::Rectangle<T>::setHorizontalRange;
    rect["setVerticalRange"]            = &juce::Rectangle<T>::setVerticalRange;
    rect["withX"]                       = &juce::Rectangle<T>::withX;
    rect["withY"]                       = &juce::Rectangle<T>::withY;
    rect["withRightX"]                  = &juce::Rectangle<T>::withRightX;
    rect["withBottomY"]                 = &juce::Rectangle<T>::withBottomY;
    rect["withZeroOrigin"]              = &juce::Rectangle<T>::withZeroOrigin;
    rect["withCentre"]                  = &juce::Rectangle<T>::withCentre;
    rect["withWidth"]                   = &juce::Rectangle<T>::withWidth;
    rect["withHeight"]                  = &juce::Rectangle<T>::withHeight;
    rect["withSize"]                    = &juce::Rectangle<T>::withSize;
    rect["withSizeKeepingCentre"]       = &juce::Rectangle<T>::withSizeKeepingCentre;
    rect["setLeft"]                     = &juce::Rectangle<T>::setLeft;
    rect["withLeft"]                    = &juce::Rectangle<T>::withLeft;
    rect["setTop"]                      = &juce::Rectangle<T>::setTop;
    rect["withTop"]                     = &juce::Rectangle<T>::withTop;
    rect["setRight"]                    = &juce::Rectangle<T>::setRight;
    rect["withRight"]                   = &juce::Rectangle<T>::withRight;
    rect["setBottom"]                   = &juce::Rectangle<T>::setBottom;
    rect["withBottom"]                  = &juce::Rectangle<T>::withBottom;
    rect["withTrimmedLeft"]             = &juce::Rectangle<T>::withTrimmedLeft;
    rect["withTrimmedRight"]            = &juce::Rectangle<T>::withTrimmedRight;
    rect["withTrimmedTop"]              = &juce::Rectangle<T>::withTrimmedTop;
    rect["withTrimmedBottom"]           = &juce::Rectangle<T>::withTrimmedBottom;
    rect["translate"]                   = &juce::Rectangle<T>::translate;
    rect["translated"]                  = &juce::Rectangle<T>::translated;
    rect["expand"]                      = &juce::Rectangle<T>::expand;
    rect["reduce"]                      = &juce::Rectangle<T>::reduce;
    rect["removeFromTop"]               = &juce::Rectangle<T>::removeFromTop;
    rect["removeFromBottom"]            = &juce::Rectangle<T>::removeFromBottom;
    rect["removeFromLeft"]              = &juce::Rectangle<T>::removeFromLeft;
    rect["removeFromRight"]             = &juce::Rectangle<T>::removeFromRight;
    rect["getConstrainedPoint"]         = &juce::Rectangle<T>::getConstrainedPoint;
    rect["getRelativePoint"]            = &juce::Rectangle<T>::template getRelativePoint<double>;
    rect["proportionOfWidth"]           = &juce::Rectangle<T>::template proportionOfWidth<double>;
    rect["proportionOfHeight"]          = &juce::Rectangle<T>::template proportionOfHeight<double>;
    rect["getIntersection"]             = &juce::Rectangle<T>::getIntersection;
    rect["getUnion"]                    = &juce::Rectangle<T>::getUnion;
    rect["enlargeIfAdjacent"]           = &juce::Rectangle<T>::enlargeIfAdjacent;
    rect["reduceIfPartlyContainedIn"]   = &juce::Rectangle<T>::reduceIfPartlyContainedIn;
    rect["constrainedWithin"]           = &juce::Rectangle<T>::constrainedWithin;
    rect["transformedBy"]               = &juce::Rectangle<T>::transformedBy;
    rect["getSmallestIntegerContainer"] = &juce::Rectangle<T>::getSmallestIntegerContainer;
    rect["toNearestInt"]                = &juce::Rectangle<T>::toNearestInt;
    rect["toNearestIntEdges"]           = &juce::Rectangle<T>::toNearestIntEdges;
    rect["toFloat"]                     = &juce::Rectangle<T>::toFloat;
    rect["toDouble"]                    = &juce::Rectangle<T>::toDouble;
    rect["toString"]                    = &juce::Rectangle<T>::toString;

    rect["leftTopRightBottom"]       = &juce::Rectangle<T>::leftTopRightBottom;
    rect["findAreaContainingPoints"] = &juce::Rectangle<T>::findAreaContainingPoints;
    rect["fromString"]               = &juce::Rectangle<T>::fromString;
}

auto juce_Rectangle(sol::table& state) -> void
{
    juce_RectangleImpl<int>(state, "RectangleInt");
    juce_RectangleImpl<float>(state, "RectangleFloat");
    juce_RectangleImpl<double>(state, "RectangleDouble");
}