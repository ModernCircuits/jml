#include "Juce.hpp"

#include "Bindings/juce_core/BigInteger.hpp"
#include "Bindings/juce_core/Random.hpp"
#include "Bindings/juce_core/Range.hpp"
#include "Bindings/juce_core/String.hpp"

#include "Bindings/juce_events/Timer.hpp"

#include "Bindings/juce_graphics/Colour.hpp"
#include "Bindings/juce_graphics/Colours.hpp"
#include "Bindings/juce_graphics/Graphics.hpp"
#include "Bindings/juce_graphics/Rectangle.hpp"

#include "Bindings/juce_gui_basics/Component.hpp"
#include "Bindings/juce_gui_basics/MouseEvent.hpp"
#include "Bindings/juce_gui_basics/MouseWheelDetails.hpp"
#include "Bindings/juce_gui_basics/Slider.hpp"
#include "Bindings/juce_gui_basics/TextButton.hpp"

#include "Bindings/juce_xtensions/LuaComponent.hpp"
#include "Bindings/juce_xtensions/LuaTimer.hpp"

auto add_juce_module(sol::state& lua) -> void
{
    sol::table juceModule = lua["juce"].get_or_create<sol::table>();

    // juce_core
    juce_BigInteger(juceModule);
    juce_Random(juceModule);
    juce_Range(juceModule);
    juce_String(juceModule);

    // juce_events
    juce_Timer(juceModule);

    // juce_graphics
    juce_Colour(juceModule);
    juce_Colours(juceModule);
    juce_Graphics(juceModule);
    juce_Rectangle(juceModule);

    // juce_gui_basics
    juce_Component(juceModule);
    juce_MouseEvent(juceModule);
    juce_TextButton(juceModule);
    juce_Slider(juceModule);

    // extra
    juce_LuaComponent(juceModule);
    juce_LuaTimer(juceModule);
}
