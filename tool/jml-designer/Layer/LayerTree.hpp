#pragma once

#include "Document/Document.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct LayerTreeItem;

struct LayerTree final
    : juce::TreeView
    , juce::ChangeBroadcaster
{
    explicit LayerTree(Document& document);
    ~LayerTree() override;

private:
    UniquePtr<LayerTreeItem> _root;
};

} // namespace mc
