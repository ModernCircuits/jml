#include "TextLayer.hpp"

#include "Component/PropertyPanel.hpp"

namespace mc {

auto setPropertyIfEmpty(juce::ValueTree& tree, juce::Identifier const& property, juce::var const& value,
                        juce::UndoManager* um)
{
    if (not tree.hasProperty(property)) { tree.setProperty(property, value, um); }
}

TextLayer::TextLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um}
{
    setPropertyIfEmpty(valueTree(), IDs::text, "Text", undoManager());
    setPropertyIfEmpty(valueTree(), IDs::fontSize, 16.0F, undoManager());
    setPropertyIfEmpty(valueTree(), IDs::fontColor, toVar(juce::Colours::black), undoManager());
}

auto TextLayer::setText(juce::String const& text) -> void { valueTree().setProperty(IDs::text, text, undoManager()); }
auto TextLayer::getText() const -> juce::String { return valueTree().getProperty(IDs::text); }

auto TextLayer::setFontSize(float fontSize) -> void { valueTree().setProperty(IDs::fontSize, fontSize, undoManager()); }
auto TextLayer::getFontSize() const -> float { return valueTree().getProperty(IDs::fontSize); }

auto TextLayer::setFontColor(juce::Colour fontColor) -> void
{
    valueTree().setProperty(IDs::fontColor, toVar(fontColor), undoManager());
}
auto TextLayer::getFontColor() const -> juce::Colour
{
    return fromVar<juce::Colour>(valueTree().getProperty(IDs::fontColor));
}

auto TextLayer::paintLayer(juce::Graphics& g) -> void
{
    g.setColour(getFontColor());
    g.setFont(getFontSize());
    g.drawText(getText(), getBounds().withZeroOrigin(), juce::Justification::centred, true);
}

auto TextLayer::addLayerProperties(juce::PropertyPanel& panel) -> void
{
    auto const properties = juce::Array<juce::PropertyComponent*>{
        makeTextProperty(valueTree(), IDs::text, "Text", true),
        makeSliderProperty(valueTree(), IDs::fontSize, "Size", 6.0, 128.0, 1.0),
        makeColorProperty(valueTree(), IDs::fontColor, "Color", true),
    };

    panel.addSection("Text", properties);
}

} // namespace mc
