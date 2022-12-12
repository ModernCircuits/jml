#include "ComponentTree.hpp"

namespace mc {

ComponentTree::ComponentTree() { addAndMakeVisible(_tree); }

auto ComponentTree::setRootComponent(juce::Component* root) -> void
{
    if (_rootItem != nullptr) { _tree.setRootItem(nullptr); }

    if (_rootComponent = root; _rootComponent != nullptr) {
        _rootItem = std::make_unique<Item>(_rootComponent);
        _tree.setRootItem(_rootItem.get());
    }
}

auto ComponentTree::resized() -> void { _tree.setBounds(getLocalBounds()); }

ComponentTree::Item::Item(juce::Component* root) : _root{root}
{
    auto const& children = root->getChildren();
    for (auto* child : children) { addSubItem(new ComponentTree::Item{child}); }
}

auto ComponentTree::Item::mightContainSubItems() -> bool { return _root->getNumChildComponents() > 0; }

auto ComponentTree::Item::getUniqueName() const -> juce::String
{
    if (_root->getComponentID().isEmpty()) { return "unknown"; }
    return _root->getComponentID();
}

auto ComponentTree::Item::itemSelectionChanged(bool isNowSelected) -> void { juce::ignoreUnused(isNowSelected); }

auto ComponentTree::Item::paintItem(juce::Graphics& g, int width, int height) -> void
{
    auto const bounds = juce::Rectangle{0, 0, width, height}.reduced(1);
    g.setColour(JmlViewerColors::whiteDirt);
    g.fillRect(bounds);

    g.setColour(JmlViewerColors::black);
    g.drawText(getUniqueName(), bounds.toFloat(), juce::Justification::centred, false);
}

} // namespace mc
