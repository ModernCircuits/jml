#include "Graphics.hpp"

#include <juce_graphics/juce_graphics.h>

auto juce_Graphics(sol::table& state) -> void
{
    // TODO(tobi):
    // fillPath
    // drawImage
    // reduceClipRegion
    // setOrigin

    // clang-format off
    auto g = state.new_usertype<juce::Graphics>("Graphics");
    g.set_function("setColour", &juce::Graphics::setColour);
    g.set_function("setOpacity", &juce::Graphics::setOpacity);
    g.set_function("setTiledImageFill", &juce::Graphics::setTiledImageFill);
    g.set_function("setFillType", &juce::Graphics::setFillType);
    g.set_function("getCurrentFont", &juce::Graphics::getCurrentFont);
    g.set_function("drawSingleLineText", &juce::Graphics::drawSingleLineText);
    g.set_function("drawMultiLineText", &juce::Graphics::drawMultiLineText);
    g.set_function("getCurrentFont", &juce::Graphics::getCurrentFont);
    g.set_function("fillCheckerBoard", &juce::Graphics::fillCheckerBoard);
    g.set_function("drawDashedLine", &juce::Graphics::drawDashedLine);
    g.set_function("drawVerticalLine", &juce::Graphics::drawVerticalLine);
    g.set_function("drawHorizontalLine", &juce::Graphics::drawHorizontalLine);
    g.set_function("strokePath", &juce::Graphics::strokePath);
    g.set_function("drawArrow", &juce::Graphics::drawArrow);
    g.set_function("setImageResamplingQuality", &juce::Graphics::setImageResamplingQuality);
    g.set_function("drawImageAt", &juce::Graphics::drawImageAt);
    g.set_function("drawImageTransformed", &juce::Graphics::drawImageTransformed);
    g.set_function("drawImageWithin", &juce::Graphics::drawImageWithin);
    g.set_function("getClipBounds", &juce::Graphics::getClipBounds);
    g.set_function("clipRegionIntersects", &juce::Graphics::clipRegionIntersects);
    g.set_function("excludeClipRegion", &juce::Graphics::excludeClipRegion);
    g.set_function("isClipEmpty", &juce::Graphics::isClipEmpty);
    g.set_function("saveState", &juce::Graphics::saveState);
    g.set_function("restoreState", &juce::Graphics::restoreState);
    g.set_function("beginTransparencyLayer", &juce::Graphics::beginTransparencyLayer);
    g.set_function("endTransparencyLayer", &juce::Graphics::endTransparencyLayer);
    g.set_function("addTransform", &juce::Graphics::addTransform);
    g.set_function("resetToDefaultState", &juce::Graphics::resetToDefaultState);
    g.set_function("isVectorDevice", &juce::Graphics::isVectorDevice);
    g.set_function("getInternalContext", &juce::Graphics::getInternalContext);

    g.set_function("setFont", sol::overload(
            static_cast<void (juce::Graphics::*)(float)>(&juce::Graphics::setFont),
            static_cast<void (juce::Graphics::*)(juce::Font const&)>(&juce::Graphics::setFont)
        )
    );
    g.set_function("drawText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* g, juce::String const& s, int x, int y, int w, int h, juce::Justification j) { g->drawText(s, x, y, w, h, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* g, juce::String const& s, juce::Rectangle<int> area, juce::Justification j) { g->drawText(s, area, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<float>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* g, juce::String const& s, juce::Rectangle<float> area, juce::Justification j) { g->drawText(s, area, j); }
        )
    );
    g.set_function("drawFittedText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* g, juce::String const& s, int x, int y, int w, int h, juce::Justification j, int m) { g->drawFittedText(s, x, y, w, h, j, m); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* g, juce::String const& s, juce::Rectangle<int> area, juce::Justification j, int m) { g->drawFittedText(s, area, j, m); }
        )
    );
    g.set_function("setGradientFill", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::ColourGradient const&)>(&juce::Graphics::setGradientFill)
        )
    );
    g.set_function("fillAll", sol::overload(
            static_cast<void (juce::Graphics::*)() const>(&juce::Graphics::fillAll),
            static_cast<void (juce::Graphics::*)(juce::Colour) const>(&juce::Graphics::fillAll)
        )
    );
    g.set_function("fillEllipse", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::fillEllipse),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>) const>(&juce::Graphics::fillEllipse)
        )
    );
    g.set_function("fillRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::fillRect)
        )
    );
    g.set_function("fillRectList", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::RectangleList<float> const&) const>(&juce::Graphics::fillRectList),
            static_cast<void (juce::Graphics::*)(juce::RectangleList<int> const&) const>(&juce::Graphics::fillRectList)
        )
    );
    g.set_function("fillRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::fillRoundedRectangle),
            [](juce::Graphics* g, juce::Rectangle<int> rect, double radius){ g->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); },
            [](juce::Graphics* g, juce::Rectangle<float> rect, double radius){ g->fillRoundedRectangle(rect, static_cast<float>(radius)); },
            [](juce::Graphics* g, juce::Rectangle<double> rect, double radius){ g->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); }
        )
    );
    g.set_function("drawRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawRect)
        )
    );
    g.set_function("drawLine", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(juce::Line<float>) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(juce::Line<float>, float) const>(&juce::Graphics::drawLine)
        )
    );
    g.set_function("drawRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float, float) const>(&juce::Graphics::drawRoundedRectangle),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float, float) const>(&juce::Graphics::drawRoundedRectangle)
        )
    );
    g.set_function("drawEllipse", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawEllipse),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::drawEllipse)
        )
    );
    // clang-format on
}
