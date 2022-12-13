#include "ToolBar.hpp"

#include "Component/Button.hpp"

namespace mc {

ToolBar::ToolBar()
{
    auto const colors = DrawableButtonColors{
        .offFill = juce::Colours::black,
        .offText = juce::Colours::transparentBlack,
        .onFill  = juce::Colours::grey,
        .onText  = juce::Colours::transparentBlack,
    };

    setImages(_select, "tool_select_svg", colors);
    setImages(_rectangle, "tool_rectangle_svg", colors);
    setImages(_ellipse, "tool_circle_svg", colors);

    addAndMakeVisible(_select);
    addAndMakeVisible(_rectangle);
    addAndMakeVisible(_ellipse);

    auto radioGroupID = juce::Random::getSystemRandom().nextInt();
    _select.setRadioGroupId(radioGroupID);
    _rectangle.setRadioGroupId(radioGroupID);
    _ellipse.setRadioGroupId(radioGroupID);

    _select.setClickingTogglesState(true);
    _rectangle.setClickingTogglesState(true);
    _ellipse.setClickingTogglesState(true);

    _select.onClick    = [this] { updateTool(); };
    _rectangle.onClick = [this] { updateTool(); };
    _ellipse.onClick   = [this] { updateTool(); };

    _select.setToggleState(true, juce::dontSendNotification);
}

auto ToolBar::resized() -> void
{
    auto area = getLocalBounds();
    _select.setBounds(area.removeFromTop(getWidth()).reduced(2));
    _rectangle.setBounds(area.removeFromTop(getWidth()).reduced(2));
    _ellipse.setBounds(area.removeFromTop(getWidth()).reduced(2));
}

auto ToolBar::updateTool() -> void
{
    auto type = ToolType::invalid;
    if (_select.getToggleState()) { type = ToolType::select; }
    if (_rectangle.getToggleState()) { type = ToolType::rectangle; }
    if (_ellipse.getToggleState()) { type = ToolType::ellipse; }

    if (onToolChange) { onToolChange(type); }
}

} // namespace mc
