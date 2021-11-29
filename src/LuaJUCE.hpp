#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

template <typename T, typename State>
auto add_juce_rectangle(State& state, char const* name) -> void
{
    // clang-format off
    auto rect = state.new_usertype<juce::Rectangle<T>>(name,
        sol::constructors<juce::Rectangle<T>(), juce::Rectangle<T>(T, T, T, T)>(),
        "x",
        sol::property(&juce::Rectangle<T>::getX, &juce::Rectangle<T>::setX),
        "y",
        sol::property(&juce::Rectangle<T>::getY, &juce::Rectangle<T>::setY)
    );
    rect.set_function("reduced", sol::overload(
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T) const noexcept>(&juce::Rectangle<T>::reduced),
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T, T) const noexcept>(&juce::Rectangle<T>::reduced)
        )
    );
    rect.set_function("reduce", &juce::Rectangle<T>::reduce);
    rect.set_function("toDouble", &juce::Rectangle<T>::toDouble);
    rect.set_function("toFloat", &juce::Rectangle<T>::toFloat);
    rect.set_function("toNearestInt", &juce::Rectangle<T>::toNearestInt);
    rect.set_function("toNearestIntEdges", &juce::Rectangle<T>::toNearestIntEdges);
    // clang-format on
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

template <typename T, typename State>
auto add_juce_range(State& state, char const* name) -> void
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

template <typename State>
auto add_juce_random(State& state) -> void
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

template <typename State>
auto add_juce_component(State& state) -> void
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

template <typename State>
auto add_juce_string(State& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::String>("String",
        sol::constructors<juce::String(), juce::String(char const*)>()
    );
    // clang-format on
}

template <typename State>
auto add_juce_textbutton(State& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::TextButton>("TextButton",
        sol::constructors<juce::TextButton(), juce::TextButton(juce::String const&), juce::TextButton(juce::String const&, juce::String const&)>(),
        sol::base_classes, sol::bases<juce::Component>()
    );
    button["onClick"] = &juce::Button::onClick;
    // clang-format on
}

auto add_juce_module(sol::state& lua) -> void
{
    auto juceModule = lua["juce"].get_or_create<sol::table>();
    add_juce_rectangle<int>(juceModule, "RectangleInt");
    add_juce_rectangle<float>(juceModule, "RectangleFloat");
    add_juce_rectangle<double>(juceModule, "RectangleDouble");
    add_juce_range<int>(juceModule, "RangeInt");
    add_juce_range<float>(juceModule, "RangeFloat");
    add_juce_range<double>(juceModule, "RangeDouble");
    add_juce_colour(juceModule);
    add_juce_graphics(juceModule);
    add_juce_random(juceModule);
    add_juce_mouse_event(juceModule);
    add_juce_string(juceModule);
    add_juce_component(juceModule);
    add_juce_textbutton(juceModule);
}
