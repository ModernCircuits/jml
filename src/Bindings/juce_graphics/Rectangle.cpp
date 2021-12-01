#include "Rectangle.hpp"

#include <juce_graphics/juce_graphics.h>

template <typename T>
auto juce_RectangleImpl(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto rect = state.new_usertype<juce::Rectangle<T>>(name,
        sol::constructors<
            juce::Rectangle<T>(),
            juce::Rectangle<T>(T, T, T, T)
        >()
    );
    rect["reduced"] = sol::overload(
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T) const noexcept>(&juce::Rectangle<T>::reduced),
            static_cast<juce::Rectangle<T> (juce::Rectangle<T>::*)(T, T) const noexcept>(&juce::Rectangle<T>::reduced)
    );
    // clang-format on

    rect["getX"]              = &juce::Rectangle<T>::getX;
    rect["setX"]              = &juce::Rectangle<T>::setX;
    rect["getY"]              = &juce::Rectangle<T>::getY;
    rect["setY"]              = &juce::Rectangle<T>::setY;
    rect["getWidth"]          = &juce::Rectangle<T>::getWidth;
    rect["setWidth"]          = &juce::Rectangle<T>::setWidth;
    rect["getHeight"]         = &juce::Rectangle<T>::getHeight;
    rect["setHeight"]         = &juce::Rectangle<T>::setHeight;
    rect["translate"]         = &juce::Rectangle<T>::translate;
    rect["translated"]        = &juce::Rectangle<T>::translated;
    rect["removeFromTop"]     = &juce::Rectangle<T>::removeFromTop;
    rect["removeFromBottom"]  = &juce::Rectangle<T>::removeFromBottom;
    rect["removeFromLeft"]    = &juce::Rectangle<T>::removeFromLeft;
    rect["removeFromRight"]   = &juce::Rectangle<T>::removeFromRight;
    rect["toDouble"]          = &juce::Rectangle<T>::toDouble;
    rect["toFloat"]           = &juce::Rectangle<T>::toFloat;
    rect["toNearestInt"]      = &juce::Rectangle<T>::toNearestInt;
    rect["isEmpty"]           = &juce::Rectangle<T>::isEmpty;
    rect["isFinite"]          = &juce::Rectangle<T>::isFinite;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["toNearestIntEdges"] = &juce::Rectangle<T>::toNearestIntEdges;
    rect["reduce"]            = &juce::Rectangle<T>::reduce;
}

auto juce_Rectangle(sol::table& state) -> void
{
    juce_RectangleImpl<int>(state, "RectangleInt");
    juce_RectangleImpl<float>(state, "RectangleFloat");
    juce_RectangleImpl<double>(state, "RectangleDouble");
}