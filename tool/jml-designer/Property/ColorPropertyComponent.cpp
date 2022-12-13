#include "ColorPropertyComponent.hpp"

#include "Core/ValueTree.hpp"

namespace mc {

ColorPropertyComponent::ColorPropertyComponent(juce::Value const& valueToControl, juce::String const& propertyName,
                                               bool showAlpha)
    : ValuePropertyComponent(valueToControl, propertyName), _container(value(), showAlpha)
{
    addAndMakeVisible(_container);
}

auto ColorPropertyComponent::refresh() -> void { repaint(); }

auto ColorPropertyComponent::paint(juce::Graphics& g) -> void
{
    PropertyComponent::paint(g);

    g.setColour(findColour(juce::BooleanPropertyComponent::backgroundColourId));
    g.fillRect(_container.getBounds());

    g.setColour(findColour(juce::BooleanPropertyComponent::outlineColourId));
    g.drawRect(_container.getBounds());
}

ColorPropertyComponent::Container::Container(juce::Value& v, bool a) : value(v), alpha(a) {}

auto ColorPropertyComponent::Container::paint(juce::Graphics& g) -> void
{
    auto const color = fromVar<juce::Colour>(value);

    g.setColour(color);
    g.fillRect(getLocalBounds().reduced(1));

    g.setColour(color.contrasting());
    g.drawText(color.toDisplayString(alpha), getLocalBounds(), juce::Justification::centred);
}

auto ColorPropertyComponent::Container::mouseUp(juce::MouseEvent const& event) -> void
{
    if (not event.mouseWasClicked()) { return; }

    auto cs = makeUnique<juce::ColourSelector>();
    cs->setSize(300, 280);
    cs->setCurrentColour(fromVar<juce::Colour>(value), juce::dontSendNotification);
    cs->addChangeListener(this);

    juce::CallOutBox::launchAsynchronously(std::move(cs), getScreenBounds(), nullptr);
}

auto ColorPropertyComponent::Container::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    auto* const cs = dynamic_cast<juce::ColourSelector*>(source);
    jassert(cs != nullptr);
    if (cs == nullptr) { return; }
    value = toVar(cs->getCurrentColour());
}

} // namespace mc
