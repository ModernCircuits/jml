#include "Document.hpp"

#include "Layer/Group/GroupLayer.hpp"
#include "Layer/Shape/ShapeLayer.hpp"

namespace mc {

Document::Document(juce::ValueTree valueTree, juce::UndoManager* um)
    : _valueTree{std::move(valueTree)}, _undoManager{um}
{
    auto group = makeUnique<GroupLayer>(_valueTree.getOrCreateChildWithName(GroupLayer::IDs::type, um), *um);
    group->setX(0.0F);
    group->setY(0.0F);
    group->setWidth(750.0F);
    group->setHeight(750.0F);
    group->setName("Document");
    group->valueTree().appendChild(juce::ValueTree{ShapeLayer::IDs::type}, nullptr);
    group->valueTree().appendChild(juce::ValueTree{ShapeLayer::IDs::type}, nullptr);
    group->valueTree().appendChild(juce::ValueTree{ShapeLayer::IDs::type}, nullptr);

    auto& children = group->getChildren();
    auto& green    = *children[0];
    green.setX(300.0F);
    green.setY(300.0F);
    green.setWidth(100.0F);
    green.setHeight(100.0F);
    green.setBackgroundFill(juce::Colours::green);
    green.setOpacity(1.0F);
    green.setName("Green");

    auto& black = *children[1];
    black.setX(250.0F);
    black.setY(250.0F);
    black.setWidth(250.0F);
    black.setHeight(250.0F);
    black.setBackgroundFill(juce::Colours::black);
    black.setOpacity(1.0F);
    black.setName("Black");

    auto& red = *children[2];
    red.setX(520.0F);
    red.setY(250.0F);
    red.setWidth(150.0F);
    red.setHeight(150.0F);
    red.setBackgroundFill(juce::Colours::red);
    red.setOpacity(1.0F);
    red.setName("Red");

    _root = std::move(group);
}

auto Document::getRootLayer() const -> Layer* { return _root.get(); }
auto Document::getValueTree() -> juce::ValueTree& { return _valueTree; }
auto Document::getValueTree() const -> juce::ValueTree const& { return _valueTree; }
auto Document::getUndoManager() const -> juce::UndoManager* { return _undoManager; }

auto Document::save(juce::File const& file) -> void
{
    if (file == juce::File{}) { return; }
    saveValueTree(getValueTree(), file, true);
}

auto Document::load(juce::File const& file, juce::UndoManager* um) -> UniquePtr<Document>
{
    auto vt = loadValueTree(file, true);
    if (not vt.isValid()) { return {}; }
    if (not vt.hasType("JML")) { return {}; }
    return makeUnique<Document>(std::move(vt), um);
}

} // namespace mc
