#include "Layer.hpp"

#include "Core/ValueTree.hpp"

namespace mc {

Layer::Layer(juce::ValueTree vt, juce::UndoManager& um) : ValueTreeObject{std::move(vt), &um}
{
    if (not valueTree().hasProperty(IDs::uuid)) {
        valueTree().setProperty(IDs::uuid, juce::Uuid{}.toString(), undoManager());
    }
    if (not valueTree().hasProperty(IDs::bounds)) {
        auto const bounds = juce::Rectangle{getX(), getY(), getWidth(), getHeight()};
        valueTree().setProperty(IDs::bounds, bounds.toString(), undoManager());
    }
    valueTree().addListener(this);
}

Layer::~Layer()
{
    valueTree().removeListener(this);
    masterReference.clear();
}

auto Layer::paint(juce::Graphics& g) -> void { juce::ignoreUnused(g); }

auto Layer::resized() -> void {}

auto Layer::getCanvas() -> juce::Component& { return _canvas; }

auto Layer::getCanvas() const -> juce::Component const& { return _canvas; }

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
auto Layer::setBounds(juce::Rectangle<float> bounds) -> void
{
    setX(bounds.getX());
    setY(bounds.getX());
    setWidth(bounds.getWidth());
    setHeight(bounds.getHeight());
}

Layer::Canvas::Canvas(Layer& layer) : _layer{layer} {}

auto Layer::Canvas::layer() -> Layer& { return _layer; }
auto Layer::Canvas::layer() const -> Layer const& { return _layer; }

auto Layer::Canvas::paint(juce::Graphics& g) -> void { _layer.paint(g); }
auto Layer::Canvas::resized() -> void { _layer.resized(); }

} // namespace mc
