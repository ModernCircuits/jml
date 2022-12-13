#pragma once

#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct Layer;
struct LayerCanvas;

struct LayerIDs
{
    inline static constexpr auto const* uuid = "uuid";
    inline static constexpr auto const* name = "name";

    inline static constexpr auto const* x      = "x";
    inline static constexpr auto const* y      = "y";
    inline static constexpr auto const* width  = "width";
    inline static constexpr auto const* height = "height";
    inline static constexpr auto const* bounds = "bounds";

    inline static constexpr auto const* background = "background";
    inline static constexpr auto const* opacity    = "opacity";
};

struct LayerListener
{
    LayerListener()          = default;
    virtual ~LayerListener() = default;

    virtual auto layerPropertyChanged(Layer& layer) -> void = 0;
};

struct Layer
    : ValueTreeObject
    , juce::ValueTree::Listener
{
    using IDs      = LayerIDs;
    using Listener = LayerListener;

    Layer(juce::ValueTree vt, juce::UndoManager& um);
    ~Layer() override;

    [[nodiscard]] virtual auto makeCanvas() -> UniquePtr<LayerCanvas> = 0;

    auto setName(juce::String const& newName) -> void;
    [[nodiscard]] auto getName() const -> juce::String;

    auto setBackground(juce::Colour newColor) -> void;
    [[nodiscard]] auto getBackground() const -> juce::Colour;

    auto setOpacity(float newOpacity) -> void;
    [[nodiscard]] auto getOpacity() const -> float;

    auto setX(float x) -> void;
    [[nodiscard]] auto getX() const -> float;

    auto setY(float y) -> void;
    [[nodiscard]] auto getY() const -> float;

    auto setWidth(float width) -> void;
    [[nodiscard]] auto getWidth() const -> float;

    auto setHeight(float height) -> void;
    [[nodiscard]] auto getHeight() const -> float;

    auto setBounds(juce::Rectangle<float> bounds) -> void;
    [[nodiscard]] auto getBounds() const -> juce::Rectangle<float>;

    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

protected:
    auto valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void override;

    juce::ListenerList<Listener> _listeners;

private:
    juce::WeakReference<Layer>::Master masterReference; // NOLINT
    friend class juce::WeakReference<Layer>;
};

} // namespace mc
