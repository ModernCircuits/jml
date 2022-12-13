#include "DocumentCanvas.hpp"

#include "Layer/LayerCanvas.hpp"
#include "Layer/Rectangle/RectangleLayer.hpp"
#include "Tool/SelectionTool.hpp"
#include "Tool/ShapeTool.hpp"

namespace mc {

DocumentCanvas::DocumentCanvas(Document& doc, ToolBar& toolBar)
    : _document{doc}, _tool{makeUnique<SelectionTool>(*this)}, _canvas{_document.rootLayer()->makeCanvas()}
{
    addAndMakeVisible(_canvas.get());
    toolBar.onToolChange = [this](ToolType type) { updateTool(type); };
}

DocumentCanvas::~DocumentCanvas() { _canvas.reset(nullptr); }

auto DocumentCanvas::document() -> Document& { return _document; }

auto DocumentCanvas::document() const -> Document const& { return _document; }

auto DocumentCanvas::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::lightgrey.brighter(0.75F)); }

auto DocumentCanvas::paintOverChildren(juce::Graphics& g) -> void
{
    if (_tool) { _tool->paintTool(g); }
}

auto DocumentCanvas::resized() -> void
{
    jassert(_canvas != nullptr);
    _canvas->setBounds(getLocalBounds());
}

auto DocumentCanvas::updateTool(ToolType type) -> void
{
    _tool.reset(nullptr);
    if (type == ToolType::select) { _tool = makeUnique<SelectionTool>(*this); }
    if (type == ToolType::rectangle) { _tool = makeUnique<ShapeTool>(*this, Shape::Rectangle); }
    if (type == ToolType::ellipse) { _tool = makeUnique<ShapeTool>(*this, Shape::Ellipse); }
    repaint();
}
} // namespace mc
