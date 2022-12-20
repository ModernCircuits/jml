#pragma once

#include "Layer/Layer.hpp"

namespace mc {

struct TextLayerIDs : Layer::IDs
{
    inline static constexpr auto const* type          = "Text";
    inline static constexpr auto const* text          = "text";
    inline static constexpr auto const* justification = "justification";
    inline static constexpr auto const* fontSize      = "fontSize";
    inline static constexpr auto const* fontColor     = "fontColor";
};

struct TextLayer final : Layer
{
    using IDs = TextLayerIDs;

    TextLayer(juce::ValueTree vt, juce::UndoManager& um);
    ~TextLayer() override = default;

    auto setText(juce::String const& text) -> void;
    [[nodiscard]] auto getText() const -> juce::String;

    auto setTextJustification(juce::Justification const& justification) -> void;
    [[nodiscard]] auto getTextJustification() const -> juce::Justification;

    auto setFontSize(float fontSize) -> void;
    [[nodiscard]] auto getFontSize() const -> float;

    auto setFontColor(juce::Colour fontColor) -> void;
    [[nodiscard]] auto getFontColor() const -> juce::Colour;

    auto paintLayer(juce::Graphics& g) -> void override;
    auto addLayerProperties(juce::PropertyPanel& panel) -> void override;
};

} // namespace mc
