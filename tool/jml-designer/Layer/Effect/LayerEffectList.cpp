#include "LayerEffectList.hpp"

#include "Layer/Effect/DropShadowLayerEffect.hpp"
#include "Layer/Effect/GlowLayerEffect.hpp"

namespace mc {

LayerEffectList::LayerEffectList(juce::ValueTree v, juce::UndoManager& undoManager)
    : ValueTreeObjectList<LayerEffect>(v), _undoManager{undoManager}
{
    rebuildObjects();
}

LayerEffectList::~LayerEffectList() { freeObjects(); }

auto LayerEffectList::isSuitableType(juce::ValueTree const& v) const -> bool
{
    auto const type = v.getType().toString();
    if (type == DropShadowLayerEffect::IDs::type) { return true; }
    if (type == GlowLayerEffect::IDs::type) { return true; }
    return false;
}

auto LayerEffectList::createNewObject(juce::ValueTree const& v) -> LayerEffect*
{
    auto const type = v.getType().toString();
    if (type == DropShadowLayerEffect::IDs::type) { return new DropShadowLayerEffect{v, _undoManager}; }
    if (type == GlowLayerEffect::IDs::type) { return new GlowLayerEffect{v, _undoManager}; }
    return nullptr;
}

auto LayerEffectList::deleteObject(LayerEffect* c) -> void { delete c; }

auto LayerEffectList::newObjectAdded(LayerEffect* layer) -> void
{
    if (onAdded) { onAdded(layer); }
}

auto LayerEffectList::objectRemoved(LayerEffect* layer) -> void
{
    if (onRemoved) { onRemoved(layer); }
}

auto LayerEffectList::objectOrderChanged() -> void
{
    if (onOrderChanged) { onOrderChanged(); }
}

} // namespace mc
