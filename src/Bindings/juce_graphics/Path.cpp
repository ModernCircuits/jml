#include "Path.hpp"

#include <juce_graphics/juce_graphics.h>

auto juce_Path(sol::table& state) -> void
{
    // TODO(tobi)
    // path["defaultToleranceForTesting"]     = std::cref(juce::Path::defaultToleranceForTesting);
    // path["defaultToleranceForMeasurement"] = std::cref(juce::Path::defaultToleranceForMeasurement);
    // lineTo
    // quadraticTo
    // cubicTo
    // addRectangle
    // addRoundedRectangle
    // addTriangle
    // addEllipse
    // addPieSegment
    // addPath
    // getTransformToScaleToFit

    // clang-format off
    auto path = state.new_usertype<juce::Path>("Path",
        sol::constructors<juce::Path()>()
    );
    path["contains"] = sol::overload(
            [] (juce::Path* self, float x, float y) -> bool { return self->contains(x, y); },
            static_cast<bool (juce::Path::*)(float,float,float) const>(&juce::Path::contains),
            static_cast<bool (juce::Path::*)(juce::Point<float>, float) const>(&juce::Path::contains)
    );
    path["intersectsLine"] = sol::overload(
            [] (juce::Path* self, juce::Line<float> line) -> bool { return self->intersectsLine(line); },
            static_cast<bool (juce::Path::*)(juce::Line<float>, float)>(&juce::Path::intersectsLine)
    );
    // clang-format on

    path["isEmpty"]                      = &juce::Path::isEmpty;
    path["getBounds"]                    = &juce::Path::getBounds;
    path["getBoundsTransformed"]         = &juce::Path::getBoundsTransformed;
    path["clear"]                        = &juce::Path::clear;
    path["getClippedLine"]               = &juce::Path::getClippedLine;
    path["getLength"]                    = &juce::Path::getLength;
    path["getPointAlongPath"]            = &juce::Path::getPointAlongPath;
    path["getNearestPoint "]             = &juce::Path::getNearestPoint;
    path["closeSubPath"]                 = &juce::Path::closeSubPath;
    path["getCurrentPosition"]           = &juce::Path::getCurrentPosition;
    path["addQuadrilateral"]             = &juce::Path::addQuadrilateral;
    path["addArc"]                       = &juce::Path::addArc;
    path["addCentredArc"]                = &juce::Path::addCentredArc;
    path["addLineSegment"]               = &juce::Path::addLineSegment;
    path["addArrow"]                     = &juce::Path::addArrow;
    path["addPolygon"]                   = &juce::Path::addPolygon;
    path["addStar"]                      = &juce::Path::addStar;
    path["addBubble"]                    = &juce::Path::addBubble;
    path["swapWithPath"]                 = &juce::Path::swapWithPath;
    path["preallocateSpace"]             = &juce::Path::preallocateSpace;
    path["applyTransform"]               = &juce::Path::applyTransform;
    path["scaleToFit"]                   = &juce::Path::scaleToFit;
    path["createPathWithRoundedCorners"] = &juce::Path::createPathWithRoundedCorners;
    path["setUsingNonZeroWinding"]       = &juce::Path::setUsingNonZeroWinding;
    path["isUsingNonZeroWinding"]        = &juce::Path::isUsingNonZeroWinding;
    path["loadPathFromStream"]           = &juce::Path::loadPathFromStream;
    path["loadPathFromData"]             = &juce::Path::loadPathFromData;
    path["writePathToStream"]            = &juce::Path::writePathToStream;
    path["toString"]                     = &juce::Path::toString;
    path["restoreFromString"]            = &juce::Path::restoreFromString;
}