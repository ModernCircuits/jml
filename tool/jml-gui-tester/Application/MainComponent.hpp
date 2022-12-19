#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <mc_gui_testing/mc_gui_testing.hpp>

namespace mc {

struct ServerConnection final : juce::InterprocessConnection
{
    ServerConnection() = default;
    ~ServerConnection() override { disconnect(); }

    auto connectionMade() -> void override
    {
        auto message        = GetGlobalComponentBounds::Request{};
        message.componentID = "foobarbaz";

        auto out  = juce::MemoryOutputStream{};
        auto tree = toValueTree(message);
        tree.writeToStream(out);
        sendMessage(out.getMemoryBlock());
    }

    auto connectionLost() -> void override { DBG("SERVER LOST"); }
    auto messageReceived(juce::MemoryBlock const& buffer) -> void override
    {
        auto in      = juce::MemoryInputStream{buffer, false};
        auto reponse = fromValueTree<GetGlobalComponentBounds::Response>(juce::ValueTree::readFromStream(in));
        DBG("CLIENT MSG: " << reponse.globalBounds.toString());
    }
};

struct Server final : juce::InterprocessConnectionServer
{
    Server()           = default;
    ~Server() override = default;

    auto createConnectionObject() -> juce::InterprocessConnection* override
    {
        _connection = std::make_unique<ServerConnection>();
        return _connection.get();
    }

    std::unique_ptr<ServerConnection> _connection;
};

struct MainComponent final : juce::Component
{
    MainComponent();
    ~MainComponent() override;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    Server _server{};
    JUCE_LEAK_DETECTOR(MainComponent) // NOLINT
};

} // namespace mc
