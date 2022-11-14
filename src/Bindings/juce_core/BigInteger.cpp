#include "BigInteger.hpp"

#include <juce_core/juce_core.h>

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
