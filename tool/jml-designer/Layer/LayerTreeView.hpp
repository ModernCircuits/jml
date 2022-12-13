#pragma once

#include "Document/Document.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

struct LayerTreeViewItem;

struct LayerTreeView final
    : juce::TreeView
    , juce::ChangeBroadcaster
{
    explicit LayerTreeView(Document& document);
    ~LayerTreeView() override;

private:
    UniquePtr<LayerTreeViewItem> _root;
};

} // namespace mc
