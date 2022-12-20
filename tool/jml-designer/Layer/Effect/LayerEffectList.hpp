#pragma once

#include "Layer/Effect/LayerEffect.hpp"

namespace mc {

struct LayerEffectList final : ValueTreeObjectList<LayerEffect>
{
    LayerEffectList(juce::ValueTree v, juce::UndoManager& undoManager);
    ~LayerEffectList() override;

    std::function<void(LayerEffect*)> onAdded{};
    std::function<void(LayerEffect*)> onRemoved{};
    std::function<void()> onOrderChanged{};

private:
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    auto createNewObject(juce::ValueTree const& v) -> LayerEffect* override;
    auto deleteObject(LayerEffect* effect) -> void override;
    auto newObjectAdded(LayerEffect* effect) -> void override;
    auto objectRemoved(LayerEffect* effect) -> void override;
    auto objectOrderChanged() -> void override;

    juce::UndoManager& _undoManager;
};

} // namespace mc
