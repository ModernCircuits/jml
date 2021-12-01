#include "MainComponent.h"

#include "Bindings/Juce.hpp"

auto const* script = R"(/home/tobante/Developer/tobanteAudio/lua-juce/src/scripts/paint.lua)";

struct LuaComponent final : juce::Component {

    LuaComponent()
    {
        _lua.open_libraries(sol::lib::base);
        add_juce_module(_lua);
        _lua["random"] = std::ref(juce::Random::getSystemRandom());
        _lua.script_file(script);
        sol::protected_function scriptConstruct = _lua["construct"];
        scriptConstruct(std::ref(*static_cast<juce::Component*>(this)));

        sol::protected_function tests = _lua["unit_tests"];
        tests();
    }

    void paint(juce::Graphics& g) override
    {
        sol::protected_function scriptPaint = _lua["paint"];
        scriptPaint(std::ref(*static_cast<juce::Component*>(this)), std::ref(g));
    }

    void resized() override
    {
        sol::protected_function scriptPaint = _lua["resized"];
        scriptPaint(std::ref(*static_cast<juce::Component*>(this)));
    }

private:
    auto mouseDown(juce::MouseEvent const& event) -> void override
    {
        sol::protected_function scriptMouseDown = _lua["mouseDown"];
        scriptMouseDown(std::ref(*static_cast<juce::Component*>(this)), std::ref(event));
    }

    sol::state _lua;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LuaComponent)
};

MainComponent::MainComponent()
{
    addAndMakeVisible(_button);
    setSize(600, 400);
    _button.onClick = [this] {
        _comp = std::make_unique<LuaComponent>();
        addAndMakeVisible(*_comp);
        resized();
    };
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    _button.setBounds(area.removeFromBottom(area.proportionOfHeight(0.1)));
    if (_comp != nullptr) { _comp->setBounds(area); }
}
