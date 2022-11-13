#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {

struct LuaSuculentaLookAndFeel final : juce::LookAndFeel_V4 {
    LuaSuculentaLookAndFeel();
    ~LuaSuculentaLookAndFeel() override = default;
};

} // namespace mc