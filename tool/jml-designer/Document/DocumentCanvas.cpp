#include "DocumentCanvas.hpp"

#include "Layer/Drawable/DrawableLayer.hpp"
#include "Tool/SelectionTool.hpp"
#include "Tool/ShapeTool.hpp"

namespace mc {

DocumentCanvas::DocumentCanvas(Document& doc, ToolBar& toolBar)
    : _document{doc}, _tool{makeUnique<SelectionTool>(*this)}
{
    addAndMakeVisible(_document.getRootLayer()->getCanvas());
    toolBar.onToolChange = [this](ToolType type) { updateTool(type); };
}

DocumentCanvas::~DocumentCanvas() = default;

auto DocumentCanvas::document() -> Document& { return _document; }

auto DocumentCanvas::document() const -> Document const& { return _document; }

auto DocumentCanvas::paint(juce::Graphics& g) -> void { g.fillAll(juce::Colours::lightgrey.brighter(0.75F)); }

auto DocumentCanvas::paintOverChildren(juce::Graphics& g) -> void
{
    if (_tool) { _tool->paintTool(g); }
}

auto DocumentCanvas::resized() -> void
{
    // auto const bounds = _document.getRootLayer()->getBounds().toNearestInt();
    // _document.getRootLayer()->getCanvas().setBounds(bounds);
}

auto DocumentCanvas::updateTool(ToolType type) -> void
{
    _tool.reset(nullptr);
    if (type == ToolType::select) { _tool = makeUnique<SelectionTool>(*this); }
    if (type == ToolType::rectangle) { _tool = makeUnique<ShapeTool>(*this, Shape::Drawable); }
    if (type == ToolType::ellipse) { _tool = makeUnique<ShapeTool>(*this, Shape::Ellipse); }
    repaint();
}
} // namespace mc
