#include "ValueTree.hpp"

#include <juce_data_structures/juce_data_structures.h>

namespace mc::lua::bindings {

auto juce_ValueTree(sol::table& state) -> void
{
    // clang-format off
    auto um = state.new_usertype<juce::ValueTree>("ValueTree",
        sol::constructors<
            juce::ValueTree(),
            juce::ValueTree(juce::Identifier const&)
        >()
    );

    um["getProperty"] = sol::overload(
        [](juce::ValueTree* self, juce::Identifier const& name) { return self->getProperty(name); },
        [](juce::ValueTree* self, juce::Identifier const& name, juce::var const& val) { return self->getProperty(name, val); }
    );

    um["removeChild"] = sol::overload(
        [](juce::ValueTree* self, juce::ValueTree const& child, juce::UndoManager* um) { self->removeChild(child, um); },
        [](juce::ValueTree* self, int index, juce::UndoManager* um) { self->removeChild(index, um); }
    );

    um["fromXml"] = sol::overload(
        [](juce::String const& xml) { return juce::ValueTree::fromXml(xml); },
        [](juce::XmlElement const& xml) { return juce::ValueTree::fromXml(xml); }
    );

    // clang-format on

    um["isEquivalentTo"]                = &juce::ValueTree::isEquivalentTo;
    um["isValid"]                       = &juce::ValueTree::isValid;
    um["createCopy"]                    = &juce::ValueTree::createCopy;
    um["copyPropertiesFrom"]            = &juce::ValueTree::copyPropertiesFrom;
    um["copyPropertiesAndChildrenFrom"] = &juce::ValueTree::copyPropertiesAndChildrenFrom;
    um["getType"]                       = &juce::ValueTree::getType;
    um["hasType"]                       = &juce::ValueTree::hasType;
    um["getPropertyPointer"]            = &juce::ValueTree::getPropertyPointer;
    um["setProperty"]                   = &juce::ValueTree::setProperty;
    um["hasProperty"]                   = &juce::ValueTree::hasProperty;
    um["removeProperty"]                = &juce::ValueTree::removeProperty;
    um["removeAllProperties"]           = &juce::ValueTree::removeAllProperties;
    um["getNumProperties"]              = &juce::ValueTree::getNumProperties;
    um["getPropertyName"]               = &juce::ValueTree::getPropertyName;
    um["getPropertyAsValue"]            = &juce::ValueTree::getPropertyAsValue;
    um["getNumChildren"]                = &juce::ValueTree::getNumChildren;
    um["getChild"]                      = &juce::ValueTree::getChild;
    um["getChildWithName"]              = &juce::ValueTree::getChildWithName;
    um["getOrCreateChildWithName"]      = &juce::ValueTree::getOrCreateChildWithName;
    um["getChildWithProperty"]          = &juce::ValueTree::getChildWithProperty;
    um["addChild"]                      = &juce::ValueTree::addChild;
    um["appendChild"]                   = &juce::ValueTree::appendChild;
    um["removeAllChildren"]             = &juce::ValueTree::removeAllChildren;
    um["moveChild"]                     = &juce::ValueTree::moveChild;
    um["isAChildOf"]                    = &juce::ValueTree::isAChildOf;
    um["indexOf"]                       = &juce::ValueTree::indexOf;
    um["getParent"]                     = &juce::ValueTree::getParent;
    um["getRoot"]                       = &juce::ValueTree::getRoot;
    um["getSibling"]                    = &juce::ValueTree::getSibling;
    um["createXml"]                     = &juce::ValueTree::createXml;
    um["toXmlString"]                   = &juce::ValueTree::toXmlString;
    um["writeToStream"]                 = &juce::ValueTree::writeToStream;
    um["addListener"]                   = &juce::ValueTree::addListener;
    um["removeListener"]                = &juce::ValueTree::removeListener;
    um["setPropertyExcludingListener"]  = &juce::ValueTree::setPropertyExcludingListener;
    um["sendPropertyChangeMessage"]     = &juce::ValueTree::sendPropertyChangeMessage;
    um["getReferenceCount"]             = &juce::ValueTree::getReferenceCount;

    um["readFromStream"]   = &juce::ValueTree::readFromStream;
    um["readFromData"]     = &juce::ValueTree::readFromData;
    um["readFromGZIPData"] = &juce::ValueTree::readFromGZIPData;
}

} // namespace mc::lua::bindings
