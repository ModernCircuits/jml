#include "Graphics.hpp"

#include <juce_graphics/juce_graphics.h>
namespace mc::lua::bindings {
auto juce_Graphics(sol::table& state) -> void
{
    // TODO(tobi):
    // fillPath
    // drawImage
    // reduceClipRegion
    // setOrigin

    auto g = state.new_usertype<juce::Graphics>("Graphics");

    g["setColour"]                 = &juce::Graphics::setColour;
    g["setOpacity"]                = &juce::Graphics::setOpacity;
    g["setTiledImageFill"]         = &juce::Graphics::setTiledImageFill;
    g["setFillType"]               = &juce::Graphics::setFillType;
    g["getCurrentFont"]            = &juce::Graphics::getCurrentFont;
    g["drawSingleLineText"]        = &juce::Graphics::drawSingleLineText;
    g["drawMultiLineText"]         = &juce::Graphics::drawMultiLineText;
    g["getCurrentFont"]            = &juce::Graphics::getCurrentFont;
    g["fillCheckerBoard"]          = &juce::Graphics::fillCheckerBoard;
    g["drawDashedLine"]            = &juce::Graphics::drawDashedLine;
    g["drawVerticalLine"]          = &juce::Graphics::drawVerticalLine;
    g["drawHorizontalLine"]        = &juce::Graphics::drawHorizontalLine;
    g["strokePath"]                = &juce::Graphics::strokePath;
    g["drawArrow"]                 = &juce::Graphics::drawArrow;
    g["setImageResamplingQuality"] = &juce::Graphics::setImageResamplingQuality;
    g["drawImageAt"]               = &juce::Graphics::drawImageAt;
    g["drawImageTransformed"]      = &juce::Graphics::drawImageTransformed;
    g["drawImageWithin"]           = &juce::Graphics::drawImageWithin;
    g["getClipBounds"]             = &juce::Graphics::getClipBounds;
    g["clipRegionIntersects"]      = &juce::Graphics::clipRegionIntersects;
    g["excludeClipRegion"]         = &juce::Graphics::excludeClipRegion;
    g["isClipEmpty"]               = &juce::Graphics::isClipEmpty;
    g["saveState"]                 = &juce::Graphics::saveState;
    g["restoreState"]              = &juce::Graphics::restoreState;
    g["beginTransparencyLayer"]    = &juce::Graphics::beginTransparencyLayer;
    g["endTransparencyLayer"]      = &juce::Graphics::endTransparencyLayer;
    g["addTransform"]              = &juce::Graphics::addTransform;
    g["resetToDefaultState"]       = &juce::Graphics::resetToDefaultState;
    g["isVectorDevice"]            = &juce::Graphics::isVectorDevice;
    g["getInternalContext"]        = &juce::Graphics::getInternalContext;
    g["setFont"]                   = sol::overload(                                                          //
        static_cast<void (juce::Graphics::*)(float)>(&juce::Graphics::setFont),            //
        static_cast<void (juce::Graphics::*)(juce::Font const&)>(&juce::Graphics::setFont) //
    );

    // clang-format off
    g.set_function("drawText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, int x, int y, int w, int h, juce::Justification j) { ctx->drawText(s, x, y, w, h, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<int> area, juce::Justification j) { ctx->drawText(s, area, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<float>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<float> area, juce::Justification j) { ctx->drawText(s, area, j); }
        )
    );
    g.set_function("drawFittedText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* ctx, juce::String const& s, int x, int y, int w, int h, juce::Justification j, int m) { ctx->drawFittedText(s, x, y, w, h, j, m); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<int> area, juce::Justification j, int m) { ctx->drawFittedText(s, area, j, m); }
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
            [](juce::Graphics* ctx, juce::Rectangle<int> rect, double radius){ ctx->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); },
            [](juce::Graphics* ctx, juce::Rectangle<float> rect, double radius){ ctx->fillRoundedRectangle(rect, static_cast<float>(radius)); },
            [](juce::Graphics* ctx, juce::Rectangle<double> rect, double radius){ ctx->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); }
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
} // namespace mc::lua::bindings
