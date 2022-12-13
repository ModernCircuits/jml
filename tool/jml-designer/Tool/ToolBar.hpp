#pragma once

#include "Tool/Tool.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {
struct AbstractShape;

struct ToolBar final : juce::Component
{
    ToolBar();
    ~ToolBar() override = default;

    auto resized() -> void override;

    std::function<void(ToolType)> onToolChange{};

private:
    auto updateTool() -> void;

    juce::DrawableButton _select{"Select", juce::DrawableButton::ImageFitted};
    juce::DrawableButton _rectangle{"Drawable", juce::DrawableButton::ImageFitted};
    juce::DrawableButton _ellipse{"Ellipse", juce::DrawableButton::ImageFitted};
};

} // namespace mc
