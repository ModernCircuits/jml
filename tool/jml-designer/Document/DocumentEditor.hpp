#pragma once

#include "Document/DocumentCanvas.hpp"
#include "Layer/LayerPropertyPanel.hpp"
#include "Layer/LayerTreeView.hpp"
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
    LayerTreeView _layerTree{_document};
    LayerPropertyPanel _propertyPanel{_layerTree};
};

} // namespace mc
