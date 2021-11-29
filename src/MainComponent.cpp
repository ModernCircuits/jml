#include "MainComponent.h"

#include "LuaJUCE.hpp"

auto const* script = R"(C:\Developer\moderncircuits\tests\juce-lua\src\scripts\paint.lua)";

MainComponent::MainComponent()
{
    _lua.open_libraries(sol::lib::base);
    add_juce_module(_lua);
    _lua["random"] = std::ref(juce::Random::getSystemRandom());
    _lua.script_file(script);

    setSize(600, 400);
}

void MainComponent::paint(juce::Graphics& g)
{
    sol::protected_function scriptPaint = _lua["paint"];
    scriptPaint(std::ref(*static_cast<juce::Component*>(this)), std::ref(g));
}

void MainComponent::resized() { }

auto MainComponent::mouseDown(juce::MouseEvent const& event) -> void
{
    sol::protected_function scriptMouseDown = _lua["mouseDown"];
    scriptMouseDown(std::ref(*static_cast<juce::Component*>(this)), std::ref(event));
}
