#pragma once

#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>
#include <mc_gui_extra/mc_gui_extra.hpp>

namespace mc {

struct Layer;

struct LayerList final : ValueTreeObjectList<Layer>
{
    LayerList(juce::ValueTree v, juce::UndoManager& undoManager);
    ~LayerList() override;

    std::function<void(Layer*)> onAdded{};
    std::function<void(Layer*)> onRemoved{};
    std::function<void()> onOrderChanged{};

private:
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    auto createNewObject(juce::ValueTree const& v) -> Layer* override;
    auto deleteObject(Layer* c) -> void override;
    auto newObjectAdded(Layer* layer) -> void override;
    auto objectRemoved(Layer* layer) -> void override;
    auto objectOrderChanged() -> void override;

    juce::UndoManager& _undoManager;
};

struct LayerListener
{
    virtual ~LayerListener() = default;

    virtual auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void;
    virtual auto layerChildrenChanged(Layer* layer) -> void;
    virtual auto layerSelectionChanged(Layer* layer) -> void;
    virtual auto layerBeingDeleted(Layer* layer) -> void;
};

struct LayerCanvas final
    : juce::Component
    , LayerListener
{
    ~LayerCanvas() override;

    [[nodiscard]] auto layer() -> Layer&;
    [[nodiscard]] auto layer() const -> Layer const&;

    auto paint(juce::Graphics& g) -> void override;
    auto paintOverChildren(juce::Graphics& g) -> void override;
    auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void override;

private:
    explicit LayerCanvas(Layer& layer);

    friend Layer;
    Layer& _layer;
};

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
    LayerList _children{valueTree(), *undoManager()};
    bool _selected{false};

    juce::WeakReference<Layer>::Master masterReference; // NOLINT
    friend class juce::WeakReference<Layer>;
};

} // namespace mc
