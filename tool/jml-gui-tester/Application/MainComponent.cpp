#include "MainComponent.hpp"

namespace mc {

MainComponent::MainComponent()
{
    if (not _server.beginWaitingForSocket(14430)) { jassertfalse; }
    DBG(_server.getBoundPort());
    setSize(1280, 720);
}

MainComponent::~MainComponent()
{
    _server.stop();
    setLookAndFeel(nullptr);
}

auto MainComponent::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::white); }

void MainComponent::resized() {}

} // namespace mc
