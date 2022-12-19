#include "OutputStream.hpp"

#include <juce_core/juce_core.h>

namespace mc::lua::bindings {
auto juce_OutputStream(sol::table& state) -> void
{
    auto stream                    = state.new_usertype<juce::OutputStream>("OutputStream", sol::no_constructor);
    stream["flush"]                = &juce::OutputStream::flush;
    stream["setPosition"]          = &juce::OutputStream::setPosition;
    stream["getPosition"]          = &juce::OutputStream::getPosition;
    stream["write"]                = &juce::OutputStream::write;
    stream["writeByte"]            = &juce::OutputStream::writeByte;
    stream["writeBool"]            = &juce::OutputStream::writeBool;
    stream["writeShort"]           = &juce::OutputStream::writeShort;
    stream["writeShortBigEndian"]  = &juce::OutputStream::writeShortBigEndian;
    stream["writeInt"]             = &juce::OutputStream::writeInt;
    stream["writeIntBigEndian"]    = &juce::OutputStream::writeIntBigEndian;
    stream["writeInt64"]           = &juce::OutputStream::writeInt64;
    stream["writeInt64BigEndian"]  = &juce::OutputStream::writeInt64BigEndian;
    stream["writeFloat"]           = &juce::OutputStream::writeFloat;
    stream["writeFloatBigEndian"]  = &juce::OutputStream::writeFloatBigEndian;
    stream["writeDouble"]          = &juce::OutputStream::writeDouble;
    stream["writeDoubleBigEndian"] = &juce::OutputStream::writeDoubleBigEndian;
    stream["writeRepeatedByte"]    = &juce::OutputStream::writeRepeatedByte;
    stream["writeCompressedInt"]   = &juce::OutputStream::writeCompressedInt;
    stream["writeString"]          = &juce::OutputStream::writeString;
    stream["writeText"]            = &juce::OutputStream::writeText;
    stream["writeFromInputStream"] = &juce::OutputStream::writeFromInputStream;
    stream["setNewLineString"]     = &juce::OutputStream::setNewLineString;
    stream["getNewLineString"]     = &juce::OutputStream::getNewLineString;
}
} // namespace mc::lua::bindings
