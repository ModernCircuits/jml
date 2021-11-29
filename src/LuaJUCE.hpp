#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace mc {
template <typename T, typename State>
auto add_juce_rectangle(State& state, char const* name) -> void
{
    state.new_usertype<juce::Rectangle<T>>(name,
        sol::constructors<juce::Rectangle<T>(), juce::Rectangle<T>(T, T, T, T)>(),
        "x",
        sol::property(&juce::Rectangle<T>::getX, &juce::Rectangle<T>::setX),
        "y",
        sol::property(&juce::Rectangle<T>::getY, &juce::Rectangle<T>::setY));
}

template <typename State>
auto add_juce_colour(State& state) -> void
{
    state.new_usertype<juce::Colour>("Colour",
        sol::constructors<juce::Colour(), juce::Colour(juce::uint8, juce::uint8, juce::uint8, juce::uint8)>());
}

template <typename State>
auto add_juce_graphics(State& state) -> void
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

template <typename State>
auto add_juce_random(State& state) -> void
{
    auto rand = state.new_usertype<juce::Random>("Random");
    rand.set_function("nextBool", &juce::Random::nextBool);
    rand.set_function("nextFloat", &juce::Random::nextFloat);
    rand.set_function("nextDouble", &juce::Random::nextDouble);
    rand.set_function("nextInt", static_cast<int (juce::Random::*)() noexcept>(&juce::Random::nextInt));
}

template <typename State>
auto add_juce_mouse_event(State& state) -> void
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

auto add_juce_module(sol::state& lua) -> void
{
    auto juceModule = lua["juce"].get_or_create<sol::table>();
    add_juce_rectangle<int>(juceModule, "RectangleInt");
    add_juce_rectangle<float>(juceModule, "RectangleFloat");
    add_juce_rectangle<double>(juceModule, "RectangleDouble");

    add_juce_colour(juceModule);
    add_juce_graphics(juceModule);
    add_juce_random(juceModule);
    add_juce_mouse_event(juceModule);
}
} // namespace mc
