#include "Component.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

auto juce_Component(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::Component>("Component", sol::base_classes, sol::bases<juce::MouseListener>());
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

    comp["getLookAndFeel"]    = &juce::Component::getLookAndFeel;
    comp["setLookAndFeel"]    = &juce::Component::setLookAndFeel;
    comp["paint"]             = &juce::Component::paint;
    comp["resized"]           = &juce::Component::resized;
    comp["getName"]           = &juce::Component::getName;
    comp["setName"]           = &juce::Component::setName;
    comp["getComponentID"]    = &juce::Component::getComponentID;
    comp["setComponentID"]    = &juce::Component::setComponentID;
    comp["setVisible"]        = &juce::Component::setVisible;
    comp["isVisible"]         = &juce::Component::isVisible;
    comp["getBounds"]         = &juce::Component::getBounds;
    comp["getLocalBounds"]    = &juce::Component::getLocalBounds;
    comp["getBoundsInParent"] = &juce::Component::getBoundsInParent;
}
