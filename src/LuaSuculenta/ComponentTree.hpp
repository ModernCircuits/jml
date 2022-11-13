#pragma once

#include "LuaSuculentaColors.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct ComponentTreeItem final : juce::TreeViewItem {
    explicit ComponentTreeItem(juce::Component* root) : _root { root }
    {
        auto const& children = root->getChildren();
        for (auto* child : children) { addSubItem(new ComponentTreeItem { child }); }
    }

    ~ComponentTreeItem() override = default;

    auto mightContainSubItems() -> bool override { return _root->getNumChildComponents() > 0; }

    auto getUniqueName() const -> juce::String override
    {
        if (_root->getComponentID().isEmpty()) { return "unknown"; }
        return _root->getComponentID();
    }

    auto itemSelectionChanged(bool isNowSelected) -> void override { juce::ignoreUnused(isNowSelected); }

    auto paintItem(juce::Graphics& g, int width, int height) -> void override
    {
        auto const bounds = juce::Rectangle { 0, 0, width, height }.reduced(1);
        g.setColour(LuaSuculentaColors::whiteDirt);
        g.fillRect(bounds);

        g.setColour(LuaSuculentaColors::black);
        g.drawText(getUniqueName(), bounds.toFloat(), juce::Justification::centred, false);
    }

private:
    juce::Component* _root;
};

struct ComponentTree final : juce::Component {
    ComponentTree() { addAndMakeVisible(_tree); }
    ~ComponentTree() override = default;

    auto setRootComponent(juce::Component* root) -> void
    {
        if (_rootItem != nullptr) { _tree.setRootItem(nullptr); }

        if (_rootComponent = root; _rootComponent != nullptr) {
            _rootItem = std::make_unique<ComponentTreeItem>(_rootComponent);
            _tree.setRootItem(_rootItem.get());
        }
    }

    auto resized() -> void override { _tree.setBounds(getLocalBounds()); }

private:
    juce::Component* _rootComponent;
    std::unique_ptr<ComponentTreeItem> _rootItem { nullptr };
    juce::TreeView _tree;
};

} // namespace mc
