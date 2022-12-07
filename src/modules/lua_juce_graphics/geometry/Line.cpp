#include "Line.hpp"

#include <juce_graphics/juce_graphics.h>

template<typename T>
auto juce_LineImpl(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto rect = state.new_usertype<juce::Line<T>>(name,
        sol::constructors<
            juce::Line<T>(),
            juce::Line<T>(T, T, T, T),
            juce::Line<T>(juce::Point<T>, juce::Point<T>)
        >()
    );
    // clang-format on

    //     rect["getX"]              = &juce::Line<T>::getX;
    //     rect["setX"]              = &juce::Line<T>::setX;
    //     rect["getY"]              = &juce::Line<T>::getY;
    //     rect["setY"]              = &juce::Line<T>::setY;
    //     rect["getWidth"]          = &juce::Line<T>::getWidth;
    //     rect["setWidth"]          = &juce::Line<T>::setWidth;
    //     rect["getHeight"]         = &juce::Line<T>::getHeight;
    //     rect["setHeight"]         = &juce::Line<T>::setHeight;
    //     rect["translate"]         = &juce::Line<T>::translate;
    //     rect["translated"]        = &juce::Line<T>::translated;
    //     rect["removeFromTop"]     = &juce::Line<T>::removeFromTop;
    //     rect["removeFromBottom"]  = &juce::Line<T>::removeFromBottom;
    //     rect["removeFromLeft"]    = &juce::Line<T>::removeFromLeft;
    //     rect["removeFromRight"]   = &juce::Line<T>::removeFromRight;
    //     rect["toDouble"]          = &juce::Line<T>::toDouble;
    //     rect["toFloat"]           = &juce::Line<T>::toFloat;
    //     rect["toNearestInt"]      = &juce::Line<T>::toNearestInt;
    //     rect["isEmpty"]           = &juce::Line<T>::isEmpty;
    //     rect["isFinite"]          = &juce::Line<T>::isFinite;
    //     rect["toNearestIntEdges"] = &juce::Line<T>::toNearestIntEdges;
    //     rect["toNearestIntEdges"] = &juce::Line<T>::toNearestIntEdges;
    //     rect["toNearestIntEdges"] = &juce::Line<T>::toNearestIntEdges;
    //     rect["reduce"]            = &juce::Line<T>::reduce;
}

auto juce_Line(sol::table& state) -> void
{
    juce_LineImpl<int>(state, "LineInt");
    juce_LineImpl<float>(state, "LineFloat");
    juce_LineImpl<double>(state, "LineDouble");
}
