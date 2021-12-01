#include "Component.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_Component(sol::table& state) -> void
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
            static_cast<void (juce::Component::*)(juce::Component&, int)>(&juce::Component::addAndMakeVisible),
            [](juce::Component* self, juce::Component* child) -> void { self->addAndMakeVisible(child, -1); }
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
