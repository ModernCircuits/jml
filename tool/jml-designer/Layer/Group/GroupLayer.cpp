#include "GroupLayer.hpp"

#include "Layer/Group/GroupLayerCanvas.hpp"
#include "Layer/Drawable/DrawableLayer.hpp"

namespace mc {

GroupLayer::GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager)
    : Layer{v, undoManager}, ValueTreeObjectList<Layer>(v)
{
    if (not valueTree().hasProperty(Layer::IDs::name)) {
        valueTree().setProperty(Layer::IDs::name, IDs::type, &undoManager);
    }
    rebuildObjects();
}

GroupLayer::~GroupLayer() { freeObjects(); }

auto GroupLayer::makeCanvas() -> UniquePtr<LayerCanvas> { return makeUnique<GroupLayerCanvas>(*this); }

auto GroupLayer::isSuitableType(juce::ValueTree const& v) const -> bool
{
    if (v.getType() == juce::StringRef{DrawableLayer::IDs::type}) { return true; }
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return true; }
    return false;
}

auto GroupLayer::createNewObject(juce::ValueTree const& v) -> Layer*
{
    if (v.getType() == juce::StringRef{DrawableLayer::IDs::type}) { return new DrawableLayer{v, *undoManager()}; }
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return new GroupLayer{v, *undoManager()}; }
    return nullptr;
}

auto GroupLayer::deleteObject(Layer* c) -> void { delete c; }

auto GroupLayer::newObjectAdded(Layer* layer) -> void
{
    if (onNewObjectAdded) { onNewObjectAdded(layer); }
    objectOrderChanged();
}

auto GroupLayer::objectRemoved(Layer* layer) -> void
{
    if (onObjectRemoved) { onObjectRemoved(layer); }
    objectOrderChanged();
}

auto GroupLayer::objectOrderChanged() -> void
{
    if (onObjectOrderChanged) { onObjectOrderChanged(); }
}

} // namespace mc
