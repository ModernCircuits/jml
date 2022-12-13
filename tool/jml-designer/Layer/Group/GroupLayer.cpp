#include "GroupLayer.hpp"

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

auto GroupLayer::resized() -> void
{
    if (size() == 0) { return; }

    auto const local = getBounds().toNearestInt();
    auto newRight    = local.getX();
    auto newBottom   = local.getY();

    for (auto& layer : *this) {
        auto& canvas = layer->getCanvas();
        auto bounds  = layer->getBounds().toNearestInt();
        newRight     = std::max(newRight, bounds.getRight());
        newBottom    = std::max(newBottom, bounds.getBottom());
        canvas.setBounds(bounds);
    }

    auto const widthChanged  = newRight != local.getWidth();
    auto const heightChanged = newBottom != local.getHeight();
    if (widthChanged || heightChanged) {
        setWidth(static_cast<float>(newRight - local.getX()));
        setHeight(static_cast<float>(newBottom - local.getY()));
    }
}

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
    getCanvas().addAndMakeVisible(layer->getCanvas());
    objectOrderChanged();
}

auto GroupLayer::objectRemoved(Layer* layer) -> void
{
    getCanvas().removeChildComponent(&layer->getCanvas());
    objectOrderChanged();
}

auto GroupLayer::objectOrderChanged() -> void
{
    for (auto& layer : *this) { layer->getCanvas().toBack(); }
    resized();
}

} // namespace mc
