#pragma once

#include "LookAndFeel/JmlViewerColors.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct ComponentTree final : juce::Component
{
    ComponentTree();
    ~ComponentTree() override = default;

    auto setRootComponent(juce::Component* root) -> void;
    auto resized() -> void override;

private:
    struct Item final : juce::TreeViewItem
    {
        explicit Item(juce::Component* root);
        ~Item() override = default;

        auto mightContainSubItems() -> bool override;
        auto getUniqueName() const -> juce::String override;
        auto itemSelectionChanged(bool isNowSelected) -> void override;
        auto paintItem(juce::Graphics& g, int width, int height) -> void override;

    private:
        juce::Component* _root;
    };

    juce::Component* _rootComponent;
    std::unique_ptr<Item> _rootItem{nullptr};
    juce::TreeView _tree;
};

} // namespace mc
