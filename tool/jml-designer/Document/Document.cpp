#include "Document.hpp"

#include "Core/ValueTree.hpp"
#include "Layer/Group/GroupLayer.hpp"
#include "Layer/Drawable/DrawableLayer.hpp"

namespace mc {

Document::Document(juce::ValueTree valueTree, juce::UndoManager* um)
    : _valueTree{std::move(valueTree)}
    , _undoManager{um}
    , _root{makeUnique<GroupLayer>(_valueTree.getOrCreateChildWithName(GroupLayer::IDs::type, um), *um)}
{
    // _root->name("Document");
    // _root->valueTree().appendChild(juce::ValueTree { DrawableLayer::IDs::type }, nullptr);
    // _root->valueTree().appendChild(juce::ValueTree { DrawableLayer::IDs::type }, nullptr);
    // _root->valueTree().appendChild(juce::ValueTree { DrawableLayer::IDs::type }, nullptr);

    // auto& green = (*_root)[0];
    // green.x(300.0F);
    // green.y(300.0F);
    // green.width(100.0F);
    // green.height(100.0F);
    // green.background(juce::Colours::green);
    // green.opacity(1.0F);
    // green.name("Green");

    // auto& black = (*_root)[1];
    // black.x(250.0F);
    // black.y(250.0F);
    // black.width(250.0F);
    // black.height(250.0F);
    // black.background(juce::Colours::black);
    // black.opacity(1.0F);
    // black.name("Black");

    // auto& red = (*_root)[2];
    // red.x(520.0F);
    // red.y(250.0F);
    // red.width(150.0F);
    // red.height(150.0F);
    // red.background(juce::Colours::red);
    // red.opacity(1.0F);
    // red.name("Red");
}

auto Document::rootLayer() const -> Layer* { return _root.get(); }
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
