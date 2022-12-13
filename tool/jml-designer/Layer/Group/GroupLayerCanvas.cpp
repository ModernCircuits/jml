#include "GroupLayerCanvas.hpp"

namespace mc {

GroupLayerCanvas::GroupLayerCanvas(GroupLayer& layer) : LayerCanvas{layer}
{
    layer.addListener(this);
    layer.onNewObjectAdded     = [this](Layer* l) { addLayer(l); };
    layer.onObjectRemoved      = [this](Layer* l) { removeLayer(l); };
    layer.onObjectOrderChanged = [this]() { updateOrder(); };
    for (auto* l : layer) { addLayer(l); }
}

GroupLayerCanvas::~GroupLayerCanvas()
{
    auto& l                = *dynamic_cast<GroupLayer*>(layer());
    l.onNewObjectAdded     = nullptr;
    l.onObjectRemoved      = nullptr;
    l.onObjectOrderChanged = nullptr;
    l.removeListener(this);
}

auto GroupLayerCanvas::resized() -> void
{
    if (_layers.empty()) { return; }

    auto const local = getLocalBounds();
    auto newRight    = local.getX();
    auto newBottom   = local.getY();

    for (auto const& canvas : _layers) {
        auto bounds = canvas->layer()->getBounds().toNearestInt();
        newRight    = std::max(newRight, bounds.getRight());
        newBottom   = std::max(newBottom, bounds.getBottom());
        canvas->setBounds(bounds);
    }

    auto const widthChanged  = newRight != local.getWidth();
    auto const heightChanged = newBottom != local.getHeight();
    if (widthChanged || heightChanged) {
        layer()->setWidth(static_cast<float>(newRight - local.getX()));
        layer()->setHeight(static_cast<float>(newBottom - local.getY()));
    }
}

auto GroupLayerCanvas::layerPropertyChanged(Layer& /*layer*/) -> void
{
    repaint();
    resized();
}

auto GroupLayerCanvas::addLayer(Layer* layer) -> void
{
    auto canvas = layer->makeCanvas();
    addAndMakeVisible(*canvas);
    _layers.push_back(std::move(canvas));
    updateOrder();
}

auto GroupLayerCanvas::removeLayer(Layer* layer) -> void
{
    auto canvas = ranges::find_if(_layers, [layer](auto const& c) { return c->layer() == layer; });
    if (canvas == ranges::end(_layers)) { return; }
    removeChildComponent(canvas->get());
    std::erase(_layers, *canvas);
    updateOrder();
}

auto GroupLayerCanvas::updateOrder() -> void
{
    auto byIndex = [](auto const& lhs, auto const& rhs) {
        auto parent = lhs->layer()->valueTree().getParent();
        jassert(parent.isValid());
        return parent.indexOf(lhs->layer()->valueTree()) < parent.indexOf(rhs->layer()->valueTree());
    };

    ranges::sort(_layers, byIndex);
    for (auto& layer : _layers) { layer->toBack(); }
    resized();
}

} // namespace mc
