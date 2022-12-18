#pragma once

#include <mc_gui_extra/mc_gui_extra.hpp>
namespace mc {
auto makeTextProperty(auto& vt, auto const& id, auto const& name, bool editable)
{
    return new juce::TextPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, 64, false, editable};
}

auto makeSliderProperty(auto& vt, auto const& id, auto const& name, double minVal, double maxVal, double interval)
{
    return new juce::SliderPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, minVal, maxVal, interval};
}

auto makeColorProperty(auto& vt, auto const& id, auto const& name, bool showAlpha)
{
    return new ColorPropertyComponent{vt.getPropertyAsValue(id, nullptr), name, showAlpha};
}

} // namespace mc
