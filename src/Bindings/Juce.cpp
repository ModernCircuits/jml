#include "Juce.hpp"

#include "Bindings/juce_core/BigInteger.hpp"
#include "Bindings/juce_core/File.hpp"
#include "Bindings/juce_core/IPAddress.hpp"
#include "Bindings/juce_core/Int.hpp"
#include "Bindings/juce_core/MathConstants.hpp"
#include "Bindings/juce_core/NormalisableRange.hpp"
#include "Bindings/juce_core/Random.hpp"
#include "Bindings/juce_core/Range.hpp"
#include "Bindings/juce_core/Result.hpp"
#include "Bindings/juce_core/StatisticsAccumulator.hpp"
#include "Bindings/juce_core/String.hpp"
#include "Bindings/juce_core/Uuid.hpp"
#include "Bindings/juce_events/Timer.hpp"
#include "Bindings/juce_graphics/AffineTransform.hpp"
#include "Bindings/juce_graphics/Colour.hpp"
#include "Bindings/juce_graphics/ColourGradient.hpp"
#include "Bindings/juce_graphics/Colours.hpp"
#include "Bindings/juce_graphics/Graphics.hpp"
#include "Bindings/juce_graphics/Line.hpp"
#include "Bindings/juce_graphics/Path.hpp"
#include "Bindings/juce_graphics/Point.hpp"
#include "Bindings/juce_graphics/Rectangle.hpp"
#include "Bindings/juce_gui_basics/Component.hpp"
#include "Bindings/juce_gui_basics/Label.hpp"
#include "Bindings/juce_gui_basics/LookAndFeel.hpp"
#include "Bindings/juce_gui_basics/LookAndFeel_V4.hpp"
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
    juce_File(juceModule);
    juce_IPAddress(juceModule);
    juce_Int(juceModule);
    juce_MathConstants(juceModule);
    juce_NormalisableRange(juceModule);
    juce_Random(juceModule);
    juce_Range(juceModule);
    juce_Result(juceModule);
    juce_StatisticsAccumulator(juceModule);
    juce_String(juceModule);
    juce_Uuid(juceModule);

    // juce_events
    juce_Timer(juceModule);

    // juce_graphics
    juce_AffineTransform(juceModule);
    juce_Colour(juceModule);
    juce_ColourGradient(juceModule);
    juce_Colours(juceModule);
    juce_Graphics(juceModule);
    juce_Line(juceModule);
    juce_Path(juceModule);
    juce_Point(juceModule);
    juce_Rectangle(juceModule);

    // juce_gui_basics
    juce_Component(juceModule);
    juce_Label(juceModule);
    juce_LookAndFeel(juceModule);
    juce_LookAndFeel_V4(juceModule);
    juce_MouseEvent(juceModule);
    juce_TextButton(juceModule);
    juce_Slider(juceModule);

    // extra
    juce_LuaComponent(juceModule);
    juce_LuaTimer(juceModule);
}
