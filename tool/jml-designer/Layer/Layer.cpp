#include "Layer.hpp"

namespace mc {

Layer::Layer(juce::ValueTree vt, juce::UndoManager& um) : ValueTreeObject{std::move(vt), &um}
{
    if (not valueTree().hasProperty(IDs::uuid)) {
        valueTree().setProperty(IDs::uuid, juce::Uuid{}.toString(), undoManager());
    }
}

Layer::~Layer() { masterReference.clear(); }

auto Layer::paintLayer(juce::Graphics& g) -> void { juce::ignoreUnused(g); }

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

Layer::Canvas::Canvas(Layer& layer) : _layer{layer}
{
    _layer.valueTree().addListener(this);
    setComponentID(layer.getUUID());
}

Layer::Canvas::~Canvas() { _layer.valueTree().removeListener(this); }

auto Layer::Canvas::layer() -> Layer& { return _layer; }
auto Layer::Canvas::layer() const -> Layer const& { return _layer; }

auto Layer::Canvas::paint(juce::Graphics& g) -> void { _layer.paintLayer(g); }

auto Layer::Canvas::valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void
{
    if (tree != layer().valueTree()) { return repaint(); }

    // ID & Name
    if (property == juce::StringRef{IDs::uuid}) { setComponentID(layer().getUUID()); }
    if (property == juce::StringRef{IDs::name}) { setName(layer().getName()); }

    // Size
    auto const hasID   = [&](auto id) { return property == juce::StringRef{id}; };
    auto const sizeIDs = Array<char const*, 4>{IDs::x, IDs::y, IDs::width, IDs::height};
    if (ranges::any_of(sizeIDs, hasID)) { setBounds(layer().getBounds().toNearestInt()); }

    repaint();
}

} // namespace mc
