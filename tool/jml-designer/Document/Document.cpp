#include "Document.hpp"

#include "Layer/Drawable/DrawableLayer.hpp"
#include "Layer/Group/GroupLayer.hpp"

namespace mc {

Document::Document(juce::ValueTree valueTree, juce::UndoManager* um)
    : _valueTree{std::move(valueTree)}
    , _undoManager{um}
    , _root{makeUnique<GroupLayer>(_valueTree.getOrCreateChildWithName(GroupLayer::IDs::type, um), *um)}
{
    _root->setX(0.0F);
    _root->setY(0.0F);
    _root->setWidth(750.0F);
    _root->setHeight(750.0F);
    _root->setName("Document");
    _root->valueTree().appendChild(juce::ValueTree{DrawableLayer::IDs::type}, nullptr);
    _root->valueTree().appendChild(juce::ValueTree{DrawableLayer::IDs::type}, nullptr);
    _root->valueTree().appendChild(juce::ValueTree{DrawableLayer::IDs::type}, nullptr);

    auto& green = (*_root)[0];
    green.setX(300.0F);
    green.setY(300.0F);
    green.setWidth(100.0F);
    green.setHeight(100.0F);
    green.setBackground(juce::Colours::green);
    green.setOpacity(1.0F);
    green.setName("Green");

    auto& black = (*_root)[1];
    black.setX(250.0F);
    black.setY(250.0F);
    black.setWidth(250.0F);
    black.setHeight(250.0F);
    black.setBackground(juce::Colours::black);
    black.setOpacity(1.0F);
    black.setName("Black");

    auto& red = (*_root)[2];
    red.setX(520.0F);
    red.setY(250.0F);
    red.setWidth(150.0F);
    red.setHeight(150.0F);
    red.setBackground(juce::Colours::red);
    red.setOpacity(1.0F);
    red.setName("Red");
}

auto Document::getRootLayer() const -> Layer* { return _root.get(); }
auto Document::valueTree() -> juce::ValueTree& { return _valueTree; }
auto Document::valueTree() const -> juce::ValueTree const& { return _valueTree; }
auto Document::undoManager() const -> juce::UndoManager* { return _undoManager; }

auto Document::save(juce::File const& file) -> void
{
    if (file == juce::File{}) { return; }
    saveValueTree(valueTree(), file, true);
}

auto Document::load(juce::File const& file, juce::UndoManager* um) -> UniquePtr<Document>
{
    auto vt = loadValueTree(file, true);
    if (not vt.isValid()) { return {}; }
    if (not vt.hasType("JML")) { return {}; }
    return makeUnique<Document>(std::move(vt), um);
}

} // namespace mc
