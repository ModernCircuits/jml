#include "ShapeTool.hpp"

#include "Document/DocumentCanvas.hpp"
#include "Layer/Shape/ShapeLayer.hpp"

namespace mc {

ShapeTool::ShapeTool(DocumentCanvas& c, Shape shape) noexcept : Tool{c}, _shape{shape}
{
    canvas().addMouseListener(this, true);
}

ShapeTool::~ShapeTool() { canvas().removeMouseListener(this); }

auto ShapeTool::paintTool(juce::Graphics& g) -> void
{
    if (not _start) { return; }
    if (not _current) { return; }
    auto const area = juce::Rectangle<float>{*_start, *_current};

    g.setColour(juce::Colours::white);
    if (_shape == Shape::Drawable) { g.fillRect(area); }
    if (_shape == Shape::Ellipse) { g.fillEllipse(area); }
}

auto ShapeTool::mouseDrag(juce::MouseEvent const& event) -> void
{
    _start   = canvas().getLocalPoint(event.eventComponent, event.mouseDownPosition);
    _current = canvas().getLocalPoint(event.eventComponent, event.position);
    canvas().repaint();
}

auto ShapeTool::mouseUp(juce::MouseEvent const& /*event*/) -> void
{
    auto const id     = juce::Uuid{};
    auto const bounds = juce::Rectangle{
        juce::Point{_start->getX(), _start->getY()},
        juce::Point{_current->getX(), _current->getY()},
    };

    auto shape = juce::ValueTree{ShapeLayer::IDs::type};
    shape.setProperty(Layer::IDs::uuid, id.toString(), nullptr);
    shape.setProperty(Layer::IDs::name, ShapeLayer::IDs::type, nullptr);
    shape.setProperty(Layer::IDs::x, bounds.getX(), nullptr);
    shape.setProperty(Layer::IDs::y, bounds.getY(), nullptr);
    shape.setProperty(Layer::IDs::width, bounds.getWidth(), nullptr);
    shape.setProperty(Layer::IDs::height, bounds.getHeight(), nullptr);
    shape.setProperty(Layer::IDs::backgroundFill, toVar(juce::Colours::white), nullptr);
    shape.setProperty(Layer::IDs::opacity, 1.0F, nullptr);

    auto& doc = canvas().document();
    doc.getRootLayer()->valueTree().appendChild(shape, doc.undoManager());

    _start.reset();
    _current.reset();
    canvas().repaint();
}

} // namespace mc
