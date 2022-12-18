#include "Layer.hpp"

#include "Layer/Drawable/DrawableLayer.hpp"
#include "Layer/Group/GroupLayer.hpp"

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
    if (v.getType() == juce::StringRef{DrawableLayer::IDs::type}) { return true; }
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return true; }
    return false;
}

auto LayerList::createNewObject(juce::ValueTree const& v) -> Layer*
{
    if (v.getType() == juce::StringRef{DrawableLayer::IDs::type}) { return new DrawableLayer{v, _undoManager}; }
    if (v.getType() == juce::StringRef{GroupLayer::IDs::type}) { return new GroupLayer{v, _undoManager}; }
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

auto LayerListener::layerChildrenChanged(Layer* layer) -> void { juce::ignoreUnused(layer); }
auto LayerListener::layerBeingDeleted(Layer* layer) -> void { juce::ignoreUnused(layer); }

LayerCanvas::LayerCanvas(Layer& layer) : _layer{layer}
{
    _layer.valueTree().addListener(this);
    setComponentID(layer.getUUID());
}

LayerCanvas::~LayerCanvas() { _layer.valueTree().removeListener(this); }

auto LayerCanvas::layer() -> Layer& { return _layer; }
auto LayerCanvas::layer() const -> Layer const& { return _layer; }

auto LayerCanvas::paint(juce::Graphics& g) -> void { _layer.paintLayer(g); }

auto LayerCanvas::valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void
{
    if (tree != layer().valueTree()) { return repaint(); }

    // ID & Name
    using IDs = Layer::IDs;
    if (property == juce::StringRef{IDs::uuid}) { setComponentID(layer().getUUID()); }
    if (property == juce::StringRef{IDs::name}) { setName(layer().getName()); }

    // Size
    auto const hasID   = [&](auto id) { return property == juce::StringRef{id}; };
    auto const sizeIDs = Array<char const*, 4>{IDs::x, IDs::y, IDs::width, IDs::height};
    if (ranges::any_of(sizeIDs, hasID)) { setBounds(layer().getBounds().toNearestInt()); }

    repaint();
}

Layer::Layer(juce::ValueTree vt, juce::UndoManager& um) : ValueTreeObject{std::move(vt), &um}
{
    _children.onAdded = [this](Layer* layer) {
        jassert(mightHaveChildren());

        auto& childCanvas = layer->getCanvas();
        getCanvas().addAndMakeVisible(childCanvas);
        for (auto* l : _children) { l->getCanvas().toBack(); }
        childCanvas.setBounds(layer->getBounds().toNearestInt());
        childCanvas.repaint();

        _listeners.call(&Listener::layerChildrenChanged, this);
    };
    _children.onRemoved = [this](Layer* layer) {
        getCanvas().removeChildComponent(&layer->getCanvas());
        for (auto* l : _children) { l->getCanvas().toBack(); }
        _listeners.call(&Listener::layerChildrenChanged, this);
    };
    _children.onOrderChanged = [this]() {
        for (auto* l : _children) { l->getCanvas().toBack(); }
        _listeners.call(&Listener::layerChildrenChanged, this);
    };
    _children.rebuildObjects();

    if (not valueTree().hasProperty(IDs::uuid)) {
        valueTree().setProperty(IDs::uuid, juce::Uuid{}.toString(), undoManager());
    }
    if (not valueTree().hasProperty(IDs::name)) {
        valueTree().setProperty(IDs::name, valueTree().getType().toString(), undoManager());
    }
}

Layer::~Layer()
{
    _listeners.call(&Listener::layerBeingDeleted, this);
    masterReference.clear();
}

auto Layer::paintLayer(juce::Graphics& g) -> void { juce::ignoreUnused(g); }

auto Layer::mightHaveChildren() -> bool { return false; }

auto Layer::getCanvas() -> Canvas& { return _canvas; }

auto Layer::getCanvas() const -> Canvas const& { return _canvas; }

auto Layer::getUUID() const -> juce::String { return valueTree().getProperty(IDs::uuid).toString(); }

auto Layer::getName() const -> juce::String { return valueTree().getProperty(IDs::name).toString(); }

auto Layer::setName(juce::String const& name) -> void { valueTree().setProperty(IDs::name, name, undoManager()); }

auto Layer::getBackground() const -> juce::Colour
{
    return fromVar<juce::Colour>(valueTree().getProperty(IDs::background));
}

auto Layer::setBackground(juce::Colour newColor) -> void
{
    valueTree().setProperty(IDs::background, toVar(newColor), undoManager());
}

auto Layer::getOpacity() const -> float { return static_cast<float>(valueTree().getProperty(IDs::opacity, 1.0F)); }
auto Layer::setOpacity(float opacity) -> void { valueTree().setProperty(IDs::opacity, opacity, undoManager()); }

auto Layer::getX() const -> float { return static_cast<float>(valueTree().getProperty(IDs::x, 0.0F)); }
auto Layer::setX(float x) -> void { valueTree().setProperty(IDs::x, x, undoManager()); }

auto Layer::getY() const -> float { return static_cast<float>(valueTree().getProperty(IDs::y, 0.0F)); }
auto Layer::setY(float y) -> void { valueTree().setProperty(IDs::y, y, undoManager()); }

auto Layer::getWidth() const -> float { return static_cast<float>(valueTree().getProperty(IDs::width, 0.0F)); }
auto Layer::setWidth(float width) -> void { valueTree().setProperty(IDs::width, width, undoManager()); }

auto Layer::getHeight() const -> float { return static_cast<float>(valueTree().getProperty(IDs::height, 0.0F)); }
auto Layer::setHeight(float height) -> void { valueTree().setProperty(IDs::height, height, undoManager()); }

auto Layer::getBounds() const -> juce::Rectangle<float> { return {getX(), getY(), getWidth(), getHeight()}; }

auto Layer::getNumChildren() const -> int { return _children.size(); }

auto Layer::getChildren() const -> juce::Array<Layer*> const& { return _children.objects; }

auto Layer::addListener(Listener* listener) -> void { _listeners.add(listener); }
auto Layer::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

} // namespace mc
