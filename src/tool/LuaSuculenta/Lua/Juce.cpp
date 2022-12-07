#include "Juce.hpp"

#include <lua_juce_core/lua_juce_core.hpp>
#include <lua_juce_events/lua_juce_events.hpp>
#include <lua_juce_graphics/lua_juce_graphics.hpp>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>

auto add_juce_module(sol::state& lua) -> void
{
    sol::table juceModule = lua["juce"].get_or_create<sol::table>();

    // juce_core
    juce_Array(juceModule);
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
    juce_StringArray(juceModule);
    juce_Uuid(juceModule);
    juce_RelativeTime(juceModule);
    juce_Time(juceModule);

    // juce_events
    juce_Timer(juceModule);

    // juce_graphics
    juce_AffineTransform(juceModule);
    juce_Colour(juceModule);
    juce_ColourGradient(juceModule);
    juce_Colours(juceModule);
    juce_Font(juceModule);
    juce_Graphics(juceModule);
    juce_Image(juceModule);
    juce_ImageCache(juceModule);
    juce_Justification(juceModule);
    juce_Line(juceModule);
    juce_Path(juceModule);
    juce_Point(juceModule);
    juce_Rectangle(juceModule);

    // juce_gui_basics
    juce_Button(juceModule);
    juce_ComboBox(juceModule);
    juce_Component(juceModule);
    juce_Label(juceModule);
    juce_ListBox(juceModule);
    juce_ListBoxModel(juceModule);
    juce_LookAndFeel(juceModule);
    juce_LookAndFeel_V4(juceModule);
    juce_MouseEvent(juceModule);
    juce_TextButton(juceModule);
    juce_Slider(juceModule);

    // xtensions
    juce_LuaComponent(juceModule);
    juce_LuaLookAndFeel_V4(juceModule);
    juce_LuaTimer(juceModule);
}
