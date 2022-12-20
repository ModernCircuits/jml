#include "LayerList.hpp"

#include "Layers/GroupLayer.hpp"
#include "Layers/ShapeLayer.hpp"
#include "Layers/TextLayer.hpp"

namespace mc {

LayerList::LayerList(juce::ValueTree v, juce::UndoManager& undoManager)
    : ValueTreeObjectList<Layer>(v), _undoManager{undoManager}
{
    if (not v.hasProperty(Layer::IDs::name)) { v.setProperty(Layer::IDs::name, v.getType().toString(), &undoManager); }
    rebuildObjects();
}

LayerList::~LayerList() { freeObjects(); }

auto LayerList::isSuitableType(juce::ValueTree const& v) const -> bool
{
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return true; }
    if (v.getType() == juce::StringRef{ShapeLayer::IDs::type}) { return true; }
    if (v.getType() == juce::StringRef{TextLayer::IDs::type}) { return true; }
    return false;
}

auto LayerList::createNewObject(juce::ValueTree const& v) -> Layer*
{
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return new GroupLayer{v, _undoManager}; }
    if (v.getType() == juce::StringRef{ShapeLayer::IDs::type}) { return new ShapeLayer{v, _undoManager}; }
    if (v.getType() == juce::StringRef{TextLayer::IDs::type}) { return new TextLayer{v, _undoManager}; }
    return nullptr;
}

auto LayerList::deleteObject(Layer* c) -> void { delete c; }

auto LayerList::newObjectAdded(Layer* layer) -> void
{
    if (onAdded) { onAdded(layer); }
}

auto LayerList::objectRemoved(Layer* layer) -> void
{
    if (onRemoved) { onRemoved(layer); }
}

auto LayerList::objectOrderChanged() -> void
{
    if (onOrderChanged) { onOrderChanged(); }
}

} // namespace mc
