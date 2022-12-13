#include "Layer.hpp"

#include "Core/ValueTree.hpp"

namespace mc {

Layer::Layer(juce::ValueTree vt, juce::UndoManager& um) : ValueTreeObject{std::move(vt), &um}
{
    if (not valueTree().hasProperty(IDs::uuid)) {
        valueTree().setProperty(IDs::uuid, juce::Uuid{}.toString(), undoManager());
    }
    if (not valueTree().hasProperty(IDs::bounds)) {
        valueTree().setProperty(IDs::bounds, juce::Rectangle{x(), y(), width(), height()}.toString(), undoManager());
    }
    valueTree().addListener(this);
}

Layer::~Layer()
{
    valueTree().removeListener(this);
    masterReference.clear();
}

auto Layer::name() const -> juce::String { return valueTree().getProperty(IDs::name).toString(); }

auto Layer::name(juce::String newName) -> void { valueTree().setProperty(IDs::name, newName, undoManager()); }

auto Layer::background() const -> juce::Colour
{
    return fromVar<juce::Colour>(valueTree().getProperty(IDs::background));
}

auto Layer::background(juce::Colour newColor) -> void
{
    valueTree().setProperty(IDs::background, toVar(newColor), undoManager());
}

auto Layer::opacity() const -> float { return static_cast<float>(valueTree().getProperty(IDs::opacity, 1.0F)); }
auto Layer::opacity(float newOpacity) -> void { valueTree().setProperty(IDs::opacity, newOpacity, undoManager()); }

auto Layer::x() const -> float { return static_cast<float>(valueTree().getProperty(IDs::x, 0.0F)); }
auto Layer::x(float newX) -> void { valueTree().setProperty(IDs::x, newX, undoManager()); }

auto Layer::y() const -> float { return static_cast<float>(valueTree().getProperty(IDs::y, 0.0F)); }
auto Layer::y(float newY) -> void { valueTree().setProperty(IDs::y, newY, undoManager()); }

auto Layer::width() const -> float { return static_cast<float>(valueTree().getProperty(IDs::width, 0.0F)); }
auto Layer::width(float newWidth) -> void { valueTree().setProperty(IDs::width, newWidth, undoManager()); }

auto Layer::height() const -> float { return static_cast<float>(valueTree().getProperty(IDs::height, 0.0F)); }
auto Layer::height(float newHeight) -> void { valueTree().setProperty(IDs::height, newHeight, undoManager()); }

auto Layer::bounds() const -> juce::Rectangle<float> { return {x(), y(), width(), height()}; }
auto Layer::bounds(juce::Rectangle<float> newBounds) -> void
{
    x(newBounds.getX());
    y(newBounds.getX());
    width(newBounds.getWidth());
    height(newBounds.getHeight());
}

auto Layer::addListener(Listener* listener) -> void { _listeners.add(listener); }
auto Layer::removeListener(Listener* listener) -> void { _listeners.remove(listener); }

auto Layer::valueTreePropertyChanged(juce::ValueTree&, juce::Identifier const& /*property*/) -> void
{
    _listeners.call(&Listener::layerPropertyChanged, *this);
}

} // namespace mc
