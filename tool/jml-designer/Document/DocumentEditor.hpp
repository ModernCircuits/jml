#pragma once

#include "Component/ComponentTree.hpp"
#include "Document/DocumentCanvas.hpp"
#include "Layer/LayerPropertyPanel.hpp"
#include "Layer/LayerTree.hpp"
#include "Tool/ToolBar.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc {

struct DocumentEditor final : juce::Component
{
    explicit DocumentEditor(Document& document);
    ~DocumentEditor() override = default;

    auto resized() -> void override;

private:
    Document& _document;

    ToolBar _toolBar;
    DocumentCanvas _canvas{_document, _toolBar};
    LayerTree _layerTree{_document};
    LayerPropertyPanel _propertyPanel{_layerTree};
    ComponentTree _componentTree{};
};

} // namespace mc
