#include "Component.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

struct SolObjectSet final : juce::ReferenceCountedObject
{
    using Ptr = juce::ReferenceCountedObjectPtr<SolObjectSet>;

    SolObjectSet()           = default;
    ~SolObjectSet() override = default;

    auto contains(sol::object obj) -> bool { return _objects.count(obj) == 1U; }

    auto add(sol::object obj) -> void
    {
        if (_objects.count(obj) == 1U) { return; }
        _objects.insert(std::move(obj));
    }
    auto remove(sol::object obj) -> void
    {
        jassert(_objects.count(obj) == 1U);
        _objects.erase(obj);
    }

private:
    std::unordered_set<sol::object, sol::reference_hash> _objects;
};

auto getSolObjectSet(juce::NamedValueSet& properties) -> SolObjectSet&
{
    if (properties.contains("lua-objects")) {
        auto const& v = properties["lua-objects"];
        auto* objects = dynamic_cast<SolObjectSet*>(v.getObject());
        jassert(objects != nullptr);
        return *objects;
    }

    auto* objects = new SolObjectSet{};
    properties.set("lua-objects", objects);
    return *objects;
}

auto juce_Component(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::Component>("InternalComponent", sol::base_classes, sol::bases<juce::MouseListener>());
    // comp.set_function("addAndMakeVisible", sol::overload(
    //         static_cast<void (juce::Component::*)(juce::Component*, int)>(&juce::Component::addAndMakeVisible),
    //         static_cast<void (juce::Component::*)(juce::Component&, int)>(&juce::Component::addAndMakeVisible),
    //         [](juce::Component* self, juce::Component* child) -> void { self->addAndMakeVisible(child, -1); }
    //     )
    // );
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

    comp["setColour"]         = &juce::Component::setColour;
    comp["paint"]             = &juce::Component::paint;
    comp["resized"]           = &juce::Component::resized;
    comp["setSize"]           = &juce::Component::setSize;
    comp["getName"]           = &juce::Component::getName;
    comp["setName"]           = &juce::Component::setName;
    comp["getComponentID"]    = &juce::Component::getComponentID;
    comp["setComponentID"]    = &juce::Component::setComponentID;
    comp["setVisible"]        = &juce::Component::setVisible;
    comp["isVisible"]         = &juce::Component::isVisible;
    comp["getBounds"]         = &juce::Component::getBounds;
    comp["getLocalBounds"]    = &juce::Component::getLocalBounds;
    comp["getBoundsInParent"] = &juce::Component::getBoundsInParent;
    comp["getLookAndFeel"]    = &juce::Component::getLookAndFeel;
    comp["setLookAndFeel"]    = [](juce::Component* self, sol::object obj) -> void {
        auto& objects = getSolObjectSet(self->getProperties());
        objects.add(obj);

        auto* lnf = obj.as<juce::LookAndFeel*>();
        self->setLookAndFeel(lnf);
    };
    comp["addAndMakeVisible"] = [](juce::Component* self, sol::object obj) -> void {
        auto& objects = getSolObjectSet(self->getProperties());
        objects.add(obj);

        auto* component = obj.as<juce::Component*>();
        self->addAndMakeVisible(component);
    };
}
