#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct ComponentTree final : juce::TreeView
{
    ComponentTree() = default;
    ~ComponentTree() override;

    auto setRootComponent(juce::Component* root) -> void;

private:
    struct Item final : juce::TreeViewItem
    {
        explicit Item(juce::Component* root);
        ~Item() override = default;

        auto mightContainSubItems() -> bool override;
        [[nodiscard]] auto getUniqueName() const -> juce::String override;
        auto itemSelectionChanged(bool isNowSelected) -> void override;
        auto paintItem(juce::Graphics& g, int width, int height) -> void override;

    private:
        juce::Component::SafePointer<juce::Component> _root;
    };

    std::unique_ptr<Item> _rootItem{nullptr};
};

} // namespace mc
