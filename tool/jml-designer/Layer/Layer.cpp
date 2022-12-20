#include "Layer.hpp"

#include "Component/PropertyPanel.hpp"
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

auto LayerListener::layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void
{
    juce::ignoreUnused(layer, property);
}
auto LayerListener::layerChildrenChanged(Layer* layer) -> void { juce::ignoreUnused(layer); }
auto LayerListener::layerSelectionChanged(Layer* layer) -> void { juce::ignoreUnused(layer); }
auto LayerListener::layerBeingDeleted(Layer* layer) -> void { juce::ignoreUnused(layer); }

LayerCanvas::LayerCanvas(Layer& layer) : _layer{layer}
{
    _layer.addListener(this);
    setComponentID(layer.getUUID());
}

LayerCanvas::~LayerCanvas() { _layer.removeListener(this); }

auto LayerCanvas::layer() -> Layer& { return _layer; }
auto LayerCanvas::layer() const -> Layer const& { return _layer; }

auto LayerCanvas::paint(juce::Graphics& g) -> void
{
    g.fillAll(_layer.getBackgroundFill());
    _layer.paintLayer(g);
}

auto LayerCanvas::paintOverChildren(juce::Graphics& g) -> void { g.fillAll(_layer.getOverlayFill()); }

auto LayerCanvas::layerPropertyChanged(Layer* l, juce::Identifier const& property) -> void
{
    if (l->valueTree() != layer().valueTree()) { return repaint(); }

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

    valueTree().addListener(this);
}

Layer::~Layer()
{
    valueTree().removeListener(this);
    _listeners.call(&Listener::layerBeingDeleted, this);
    masterReference.clear();
}

auto Layer::paintLayer(juce::Graphics& g) -> void { juce::ignoreUnused(g); }

auto Layer::mightHaveChildren() -> bool { return false; }

auto Layer::fillPropertyPanel(juce::PropertyPanel& panel) -> void
{
    auto const general = juce::Array<juce::PropertyComponent*>{
        makeTextProperty(valueTree(), Layer::IDs::uuid, "UUID", false),
        makeTextProperty(valueTree(), Layer::IDs::name, "Name", true),
    };

    auto const position = juce::Array<juce::PropertyComponent*>{
        makeSliderProperty(valueTree(), Layer::IDs::x, "X", 0.0, 1000.0, 1.0),
        makeSliderProperty(valueTree(), Layer::IDs::y, "Y", 0.0, 1000.0, 1.0),
        makeSliderProperty(valueTree(), Layer::IDs::width, "Width", 0.0, 1000.0, 1.0),
        makeSliderProperty(valueTree(), Layer::IDs::height, "Height", 0.0, 1000.0, 1.0),
    };

    auto const fill = juce::Array<juce::PropertyComponent*>{
        makeSliderProperty(valueTree(), IDs::opacity, "Opacity", 0.0, 1.0, 0.01),
        makeColorProperty(valueTree(), IDs::backgroundFill, "Background", true),
        makeColorProperty(valueTree(), IDs::overlayFill, "Overlay", true),
    };

    panel.clear();
    panel.addSection("Layer", general);
    panel.addSection("Position", position);
    panel.addSection("Fill", fill);
    addLayerProperties(panel);
}
auto Layer::addLayerProperties(juce::PropertyPanel& panel) -> void { juce::ignoreUnused(panel); }

auto Layer::getCanvas() -> Canvas& { return _canvas; }

auto Layer::getCanvas() const -> Canvas const& { return _canvas; }

auto Layer::getUUID() const -> juce::String { return valueTree().getProperty(IDs::uuid).toString(); }

auto Layer::getName() const -> juce::String { return valueTree().getProperty(IDs::name).toString(); }

auto Layer::setName(juce::String const& name) -> void { valueTree().setProperty(IDs::name, name, undoManager()); }

auto Layer::getBackgroundFill() const -> juce::Colour
{
    return fromVar<juce::Colour>(valueTree().getProperty(IDs::backgroundFill));
}

auto Layer::setBackgroundFill(juce::Colour newColor) -> void
{
    valueTree().setProperty(IDs::backgroundFill, toVar(newColor), undoManager());
}
auto Layer::getOverlayFill() const -> juce::Colour
{
    return fromVar<juce::Colour>(valueTree().getProperty(IDs::overlayFill));
}

auto Layer::setOverlayFill(juce::Colour newColor) -> void
{
    valueTree().setProperty(IDs::overlayFill, toVar(newColor), undoManager());
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

auto Layer::setSelected(bool isSelected) -> void
{
    if (_selected == isSelected) { return; }
    _selected = isSelected;
    _listeners.call(&Listener::layerSelectionChanged, this);
}
auto Layer::isSelected() const -> bool { return _selected; }

auto Layer::getBounds() const -> juce::Rectangle<float> { return {getX(), getY(), getWidth(), getHeight()}; }

auto Layer::getNumChildren() const -> int { return _children.size(); }

auto Layer::getChildren() const -> juce::Array<Layer*> const& { return _children.objects; }

auto Layer::addListener(Listener* listener) -> void { _listeners.add(listener); }
auto Layer::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

auto Layer::valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void
{
    if (tree != valueTree()) { return; }
    _listeners.call(&Listener::layerPropertyChanged, this, property);
}
} // namespace mc
