#include "InputStream.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_InputStream(sol::table& state) -> void
{
    auto stream                        = state.new_usertype<juce::InputStream>("InputStream", sol::no_constructor);
    stream["getTotalLength"]           = &juce::InputStream::getTotalLength;
    stream["getNumBytesRemaining"]     = &juce::InputStream::getNumBytesRemaining;
    stream["isExhausted"]              = &juce::InputStream::isExhausted;
    stream["readByte"]                 = &juce::InputStream::readByte;
    stream["readBool"]                 = &juce::InputStream::readBool;
    stream["readShort"]                = &juce::InputStream::readShort;
    stream["readShortBigEndian"]       = &juce::InputStream::readShortBigEndian;
    stream["readInt"]                  = &juce::InputStream::readInt;
    stream["readIntBigEndian"]         = &juce::InputStream::readIntBigEndian;
    stream["readInt64"]                = &juce::InputStream::readInt64;
    stream["readInt64BigEndian"]       = &juce::InputStream::readInt64BigEndian;
    stream["readFloat"]                = &juce::InputStream::readFloat;
    stream["readFloatBigEndian"]       = &juce::InputStream::readFloatBigEndian;
    stream["readDouble"]               = &juce::InputStream::readDouble;
    stream["readDoubleBigEndian"]      = &juce::InputStream::readDoubleBigEndian;
    stream["readCompressedInt"]        = &juce::InputStream::readCompressedInt;
    stream["readNextLine"]             = &juce::InputStream::readNextLine;
    stream["readString"]               = &juce::InputStream::readString;
    stream["readEntireStreamAsString"] = &juce::InputStream::readEntireStreamAsString;
    stream["readIntoMemoryBlock"]      = &juce::InputStream::readIntoMemoryBlock;
    stream["getPosition"]              = &juce::InputStream::getPosition;
    stream["setPosition"]              = &juce::InputStream::setPosition;
    stream["skipNextBytes"]            = &juce::InputStream::skipNextBytes;
}
} // namespace mc::lua::bindings
