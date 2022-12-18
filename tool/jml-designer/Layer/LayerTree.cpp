#include "LayerTree.hpp"

#include "Layer/Group/GroupLayerTreeItem.hpp"

namespace mc {

LayerTree::LayerTree(Document& document) : _root{makeUnique<GroupLayerTreeItem>(*document.getRootLayer())}
{
    setRootItemVisible(false);
    setMultiSelectEnabled(true);
    setRootItem(_root.get());
    setIndentSize(16);
}

LayerTree::~LayerTree() { setRootItem(nullptr); }

} // namespace mc
