#include "LayerTreeView.hpp"

#include "Layer/Group/GroupLayerTreeViewItem.hpp"

namespace mc {

LayerTreeView::LayerTreeView(Document& document)
    : _root{makeUnique<GroupLayerTreeViewItem>(document.rootLayer()->valueTree(), *document.undoManager())}
{
    setRootItemVisible(false);
    setMultiSelectEnabled(true);
    setRootItem(_root.get());
    setIndentSize(16);
}

LayerTreeView::~LayerTreeView() { setRootItem(nullptr); }

} // namespace mc
