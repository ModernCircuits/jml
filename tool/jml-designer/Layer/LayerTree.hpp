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

    auto getDocument() -> Document& { return _document; }
    auto getDocument() const -> Document const& { return _document; }

private:
    Document& _document;
    UniquePtr<LayerTreeItem> _root;
};

} // namespace mc
