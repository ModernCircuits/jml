#include "Juce.hpp"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <juce_gui_extra/juce_gui_extra.h>

template <typename T>
auto juce_Rectangle(sol::table& state, char const* name) -> void
{
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

    rect["getX"]              = &juce::Rectangle<T>::getX;
    rect["setX"]              = &juce::Rectangle<T>::setX;
    rect["getY"]              = &juce::Rectangle<T>::getY;
    rect["setY"]              = &juce::Rectangle<T>::setY;
    rect["getWidth"]          = &juce::Rectangle<T>::getWidth;
    rect["setWidth"]          = &juce::Rectangle<T>::setWidth;
    rect["getHeight"]         = &juce::Rectangle<T>::getHeight;
    rect["setHeight"]         = &juce::Rectangle<T>::setHeight;
    rect["translate"]         = &juce::Rectangle<T>::translate;
    rect["translated"]        = &juce::Rectangle<T>::translated;
    rect["removeFromTop"]     = &juce::Rectangle<T>::removeFromTop;
    rect["removeFromBottom"]  = &juce::Rectangle<T>::removeFromBottom;
    rect["removeFromLeft"]    = &juce::Rectangle<T>::removeFromLeft;
    rect["removeFromRight"]   = &juce::Rectangle<T>::removeFromRight;
    rect["toDouble"]          = &juce::Rectangle<T>::toDouble;
    rect["toFloat"]           = &juce::Rectangle<T>::toFloat;
    rect["toNearestInt"]      = &juce::Rectangle<T>::toNearestInt;
    rect["isEmpty"]           = &juce::Rectangle<T>::isEmpty;
    rect["isFinite"]          = &juce::Rectangle<T>::isFinite;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["reduce"]            = &juce::Rectangle<T>::reduce;
}

auto juce_Colour(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<juce::Colour>("Colour",
        sol::constructors<
            juce::Colour(),
            juce::Colour(juce::uint8, juce::uint8, juce::uint8, juce::uint8)
        >()
    );
    // clang-format on
}

auto juce_Graphics(sol::table& state) -> void
{
    // clang-format off
    auto g = state.new_usertype<juce::Graphics>("Graphics");
    g.set_function("setColour", static_cast<void (juce::Graphics::*)(juce::Colour)>(&juce::Graphics::setColour));
    g.set_function("fillAll", sol::overload(
            static_cast<void (juce::Graphics::*)() const>(&juce::Graphics::fillAll),
            static_cast<void (juce::Graphics::*)(juce::Colour) const>(&juce::Graphics::fillAll)
        )
    );
    g.set_function("fillRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::fillRect)
        )
    );
    g.set_function("fillRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::fillRoundedRectangle),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::fillRoundedRectangle)
        )
    );
    g.set_function("drawRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawRect)
        )
    );
    g.set_function("drawRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float, float) const>(&juce::Graphics::drawRoundedRectangle),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float, float) const>(&juce::Graphics::drawRoundedRectangle)
        )
    );
    // clang-format on
}

template <typename T>
auto juce_Range(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto range = state.new_usertype<juce::Range<T>>(name,
        sol::constructors<juce::Range<T>(), juce::Range<T>(T, T)>(),
        "start",
        sol::property(&juce::Range<T>::getStart, &juce::Range<T>::setStart),
        "end",
        sol::property(&juce::Range<T>::getEnd, &juce::Range<T>::setEnd)
    );
    // clang-format on
}

auto juce_Random(sol::table& state) -> void
{
    // clang-format off
    auto rand = state.new_usertype<juce::Random>("Random");
    rand.set_function("setSeed", &juce::Random::setSeed);
    rand.set_function("getSeed", &juce::Random::getSeed);
    rand.set_function("nextBool", &juce::Random::nextBool);
    rand.set_function("nextFloat", &juce::Random::nextFloat);
    rand.set_function("nextDouble", &juce::Random::nextDouble);
    rand.set_function("nextInt64", &juce::Random::nextInt64);
    rand.set_function("nextInt", sol::overload(
            static_cast<int (juce::Random::*)() noexcept>(&juce::Random::nextInt),
            static_cast<int (juce::Random::*)(int) noexcept>(&juce::Random::nextInt),
            static_cast<int (juce::Random::*)(juce::Range<int>) noexcept>(&juce::Random::nextInt)
        )
    );
    // clang-format on
}

auto juce_MouseEvent(sol::table& state) -> void
{
    auto event           = state.new_usertype<juce::MouseEvent>("MouseEvent");
    event["x"]           = &juce::MouseEvent::x;
    event["y"]           = &juce::MouseEvent::y;
    event["pressure"]    = &juce::MouseEvent::pressure;
    event["orientation"] = &juce::MouseEvent::orientation;
    event["rotation"]    = &juce::MouseEvent::rotation;
    event["tiltX"]       = &juce::MouseEvent::tiltX;
    event["tiltY"]       = &juce::MouseEvent::tiltY;
}

auto juce_Component(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::Component>("Component");
    comp.set_function("paint",              &juce::Component::paint);
    comp.set_function("resized",            &juce::Component::resized);
    comp.set_function("getName",            &juce::Component::getName);
    comp.set_function("setName",            &juce::Component::setName);
    comp.set_function("getComponentID",     &juce::Component::getComponentID);
    comp.set_function("setComponentID",     &juce::Component::setComponentID);
    comp.set_function("setVisible",         &juce::Component::setVisible);
    comp.set_function("isVisible",          &juce::Component::isVisible);
    comp.set_function("getBounds",          &juce::Component::getBounds);
    comp.set_function("getLocalBounds",     &juce::Component::getLocalBounds);
    comp.set_function("getBoundsInParent",  &juce::Component::getBoundsInParent);
    comp.set_function("addAndMakeVisible", sol::overload(
            static_cast<void (juce::Component::*)(juce::Component*, int)>(&juce::Component::addAndMakeVisible),
            static_cast<void (juce::Component::*)(juce::Component&, int)>(&juce::Component::addAndMakeVisible)
        )
    );
    comp.set_function("setBounds", sol::overload(
            static_cast<void (juce::Component::*)(int,int,int,int)>(&juce::Component::setBounds),
            static_cast<void (juce::Component::*)(juce::Rectangle<int>)>(&juce::Component::setBounds)
        )
    );
    comp.set_function("repaint", sol::overload(
            static_cast<void (juce::Component::*)()>(&juce::Component::repaint),
            static_cast<void (juce::Component::*)(juce::Rectangle<int>)>(&juce::Component::repaint),
            static_cast<void (juce::Component::*)(int, int, int, int)>(&juce::Component::repaint)
        )
    );
    // clang-format on
}

auto juce_String(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::String>("String",
        sol::constructors<juce::String(), juce::String(char const*)>()
    );
    // clang-format on
}

auto juce_TextButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::TextButton>("TextButton",
        sol::constructors<juce::TextButton(), juce::TextButton(juce::String const&), juce::TextButton(juce::String const&, juce::String const&)>(),
        sol::base_classes, sol::bases<juce::Component>()
    );
    button["onClick"] = &juce::Button::onClick;
    // clang-format on
}

auto juce_BigInteger(sol::table& state) -> void
{
    // clang-format off
    auto bigInt = state.new_usertype<juce::BigInteger>("BigInteger",
        sol::constructors<
            juce::BigInteger(),
            juce::BigInteger(juce::uint32),
            juce::BigInteger(juce::int32),
            juce::BigInteger(juce::int64)
        >()
    );
    bigInt.set_function("setBit", sol::overload(
            static_cast<void (juce::BigInteger::*)(int)>(&juce::BigInteger::setBit),
            static_cast<void (juce::BigInteger::*)(int, bool)>(&juce::BigInteger::setBit)
        )
    );
    // clang-format on
    bigInt["swapWith"]                  = &juce::BigInteger::swapWith;
    bigInt["isZero"]                    = &juce::BigInteger::isZero;
    bigInt["isOne"]                     = &juce::BigInteger::isOne;
    bigInt["toInteger"]                 = &juce::BigInteger::toInteger;
    bigInt["toInt64"]                   = &juce::BigInteger::toInt64;
    bigInt["clear"]                     = &juce::BigInteger::clear;
    bigInt["clearBit"]                  = &juce::BigInteger::clearBit;
    bigInt["setRange"]                  = &juce::BigInteger::setRange;
    bigInt["insertBit"]                 = &juce::BigInteger::insertBit;
    bigInt["getBitRange"]               = &juce::BigInteger::getBitRange;
    bigInt["getBitRangeAsInt"]          = &juce::BigInteger::getBitRangeAsInt;
    bigInt["setBitRangeAsInt"]          = &juce::BigInteger::setBitRangeAsInt;
    bigInt["shiftBits"]                 = &juce::BigInteger::shiftBits;
    bigInt["countNumberOfSetBits"]      = &juce::BigInteger::countNumberOfSetBits;
    bigInt["findNextSetBit"]            = &juce::BigInteger::findNextSetBit;
    bigInt["findNextClearBit"]          = &juce::BigInteger::findNextClearBit;
    bigInt["getHighestBit"]             = &juce::BigInteger::getHighestBit;
    bigInt["isNegative"]                = &juce::BigInteger::isNegative;
    bigInt["setNegative"]               = &juce::BigInteger::setNegative;
    bigInt["negate"]                    = &juce::BigInteger::negate;
    bigInt["compare"]                   = &juce::BigInteger::compare;
    bigInt["compareAbsolute"]           = &juce::BigInteger::compareAbsolute;
    bigInt["divideBy"]                  = &juce::BigInteger::divideBy;
    bigInt["findGreatestCommonDivisor"] = &juce::BigInteger::findGreatestCommonDivisor;
    bigInt["exponentModulo"]            = &juce::BigInteger::exponentModulo;
    bigInt["inverseModulo"]             = &juce::BigInteger::inverseModulo;
    bigInt["montgomeryMultiplication"]  = &juce::BigInteger::montgomeryMultiplication;
    bigInt["extendedEuclidean"]         = &juce::BigInteger::extendedEuclidean;
    bigInt["toString"]                  = &juce::BigInteger::toString;
    bigInt["parseString"]               = &juce::BigInteger::parseString;
    bigInt["toMemoryBlock"]             = &juce::BigInteger::toMemoryBlock;
    bigInt["loadFromMemoryBlock"]       = &juce::BigInteger::loadFromMemoryBlock;
}

struct LuaComp : juce::Component {
    LuaComp(sol::this_state L)
        : scriptPaint(sol::make_reference<sol::function>(L.lua_state(), [](juce::Graphics&, char const*) {}))
        , scriptResized(sol::make_reference<sol::function>(L.lua_state(), []() -> void {}))
    {
    }

    ~LuaComp() override = default;

    auto paint(juce::Graphics& g) -> void override
    {
        g.fillAll(juce::Colours::pink);
        if (scriptPaint.valid()) { scriptPaint(std::ref(*this), std::ref(g), "foo"); }
    }

    auto resized() -> void override
    {
        if (scriptResized.valid()) { scriptResized(std::ref(*this)); }
    }

    sol::function scriptPaint;
    sol::function scriptResized;
};

auto juce_LuaComponent(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<LuaComp>("LuaComp",
	    sol::constructors<LuaComp(sol::this_state)>(),
        sol::base_classes, sol::bases<juce::Component>(),
	    "paint",
	    &LuaComp::scriptPaint,
        "resized",
	    &LuaComp::scriptResized
    );
    // clang-format on
}

auto add_juce_module(sol::state& lua) -> void
{
    sol::table juceModule = lua["juce"].get_or_create<sol::table>();
    juce_Rectangle<int>(juceModule, "RectangleInt");
    juce_Rectangle<float>(juceModule, "RectangleFloat");
    juce_Rectangle<double>(juceModule, "RectangleDouble");
    juce_Range<int>(juceModule, "RangeInt");
    juce_Range<float>(juceModule, "RangeFloat");
    juce_Range<double>(juceModule, "RangeDouble");
    juce_Colour(juceModule);
    juce_Graphics(juceModule);
    juce_Random(juceModule);
    juce_MouseEvent(juceModule);
    juce_String(juceModule);
    juce_Component(juceModule);
    juce_TextButton(juceModule);
    juce_BigInteger(juceModule);
    juce_LuaComponent(juceModule);
}
