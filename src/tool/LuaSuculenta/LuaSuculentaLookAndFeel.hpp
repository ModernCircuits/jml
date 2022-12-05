#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc {

struct LuaSuculentaLookAndFeel final : juce::LookAndFeel_V4 {
    LuaSuculentaLookAndFeel();
    ~LuaSuculentaLookAndFeel() override = default;
};

} // namespace mc
