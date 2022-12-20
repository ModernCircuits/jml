#pragma once

#include "Layer/Effect/LayerEffectList.hpp"
#include "Layer/LayerCanvas.hpp"
#include "Layer/LayerList.hpp"
#include "Layer/LayerListener.hpp"

namespace mc {

struct LayerIDs
{
    inline static constexpr auto const* uuid = "uuid";
    inline static constexpr auto const* name = "name";

    inline static constexpr auto const* x      = "x";
    inline static constexpr auto const* y      = "y";
    inline static constexpr auto const* width  = "width";
    inline static constexpr auto const* height = "height";

    inline static constexpr auto const* opacity        = "opacity";
    inline static constexpr auto const* backgroundFill = "backgroundFill";
    inline static constexpr auto const* overlayFill    = "overlayFill";
};

struct Layer
    : ValueTreeObject
    , juce::ValueTree::Listener
{
    using IDs      = LayerIDs;
    using Listener = LayerListener;
    using Canvas   = LayerCanvas;

    Layer(juce::ValueTree vt, juce::UndoManager& um);
    ~Layer() override;

    [[nodiscard]] virtual auto mightHaveChildren() -> bool;
    virtual auto paintLayer(juce::Graphics& g) -> void;
    virtual auto addLayerProperties(juce::PropertyPanel& panel) -> void;

    [[nodiscard]] auto getUUID() const -> juce::String;

    auto setName(juce::String const& newName) -> void;
    [[nodiscard]] auto getName() const -> juce::String;

    auto setX(float x) -> void;
    [[nodiscard]] auto getX() const -> float;

    auto setY(float y) -> void;
    [[nodiscard]] auto getY() const -> float;

    auto setWidth(float width) -> void;
    [[nodiscard]] auto getWidth() const -> float;

    auto setHeight(float height) -> void;
    [[nodiscard]] auto getHeight() const -> float;

    [[nodiscard]] auto getBounds() const -> juce::Rectangle<float>;

    [[nodiscard]] auto getCanvas() -> Canvas&;
    [[nodiscard]] auto getCanvas() const -> Canvas const&;
    auto fillPropertyPanel(juce::PropertyPanel& panel) -> void;

    auto setOpacity(float newOpacity) -> void;
    [[nodiscard]] auto getOpacity() const -> float;

    auto setBackgroundFill(juce::Colour newColor) -> void;
    [[nodiscard]] auto getBackgroundFill() const -> juce::Colour;

    auto setOverlayFill(juce::Colour newColor) -> void;
    [[nodiscard]] auto getOverlayFill() const -> juce::Colour;

    auto setSelected(bool isSelected) -> void;
    [[nodiscard]] auto isSelected() const -> bool;

    [[nodiscard]] auto getNumChildren() const -> int;
    [[nodiscard]] auto getChildren() const -> juce::Array<Layer*> const&;

    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

    auto valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void override;

private:
    juce::ListenerList<Listener> _listeners;
    Canvas _canvas{*this};
    LayerEffectList _effects{valueTree(), *undoManager()};
    LayerList _children{valueTree(), *undoManager()};
    bool _selected{false};

    juce::WeakReference<Layer>::Master masterReference; // NOLINT
    friend class juce::WeakReference<Layer>;
};

} // namespace mc
