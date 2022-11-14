#include "IPAddress.hpp"

#include <juce_core/juce_core.h>

auto juce_IPAddress(sol::table& state) -> void
{
    // clang-format off
    auto ip = state.new_usertype<juce::IPAddress>("IPAddress",
        sol::constructors<
            juce::IPAddress(),
            juce::IPAddress(juce::uint32),
            juce::IPAddress(juce::String const&),
            juce::IPAddress(juce::uint8*, bool),
            juce::IPAddress(juce::uint16*),
            juce::IPAddress(juce::uint8, juce::uint8, juce::uint8, juce::uint8),
            juce::IPAddress(juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16, juce::uint16)
        >()
    );
    // clang-format on

    ip["isNull"]   = &juce::IPAddress::isNull;
    ip["toString"] = &juce::IPAddress::toString;
    ip["compare"]  = &juce::IPAddress::compare;

    ip["any"]                            = &juce::IPAddress::any;
    ip["broadcast"]                      = &juce::IPAddress::broadcast;
    ip["findAllAddresses"]               = &juce::IPAddress::findAllAddresses;
    ip["getAllAddresses"]                = &juce::IPAddress::getAllAddresses;
    ip["getLocalAddress"]                = &juce::IPAddress::getLocalAddress;
    ip["getFormattedAddress"]            = &juce::IPAddress::getFormattedAddress;
    ip["isIPv4MappedAddress"]            = &juce::IPAddress::isIPv4MappedAddress;
    ip["convertIPv4MappedAddressToIPv4"] = &juce::IPAddress::convertIPv4MappedAddressToIPv4;
    ip["convertIPv4AddressToIPv4Mapped"] = &juce::IPAddress::convertIPv4AddressToIPv4Mapped;
    ip["getInterfaceBroadcastAddress"]   = &juce::IPAddress::getInterfaceBroadcastAddress;

    ip["address"] = &juce::IPAddress::address;
    ip["isIPv6"]  = &juce::IPAddress::isIPv6;
}
