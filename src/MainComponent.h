#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "Sol3.hpp"

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

    auto paintItem(juce::Graphics& g, int width, int height) -> void override
    {
        auto const bounds = juce::Rectangle { 0, 0, width, height }.reduced(1);
        g.setColour(juce::Colours::green);
        g.fillRect(bounds);

        g.setColour(juce::Colours::black);
        g.drawText(getUniqueName(), bounds.toFloat(), juce::Justification::centred, false);
    }

private:
    juce::Component* _root;
};
struct ComponentTree final : juce::Component {
    explicit ComponentTree(juce::Component* root) : _rootComponent { root }
    {
        _tree.setRootItem(&_rootItem);
        addAndMakeVisible(_tree);
    }

    ~ComponentTree() override = default;

    auto resized() -> void override { _tree.setBounds(getLocalBounds()); }

private:
    juce::Component* _rootComponent;
    ComponentTreeItem _rootItem { _rootComponent };
    juce::TreeView _tree;
};

struct MainComponent : juce::Component {
    MainComponent();
    ~MainComponent() override;

    void resized() override;

private:
    auto reloadScript(juce::File const& path) -> void;
    auto loadScriptPath() -> void;

    sol::state _lua;
    juce::Component* _comp { nullptr };
    juce::TextButton _select { "Select Script" };
    juce::TextButton _reload { "Reload" };

    std::unique_ptr<ComponentTree> _componentTree { nullptr };

    juce::File _currentScript;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
