#include "Juce.hpp"

#include <lua_juce_core/lua_juce_core.hpp>
#include <lua_juce_events/lua_juce_events.hpp>
#include <lua_juce_graphics/lua_juce_graphics.hpp>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>

auto add_juce_module(sol::state& lua) -> void
{
    auto table = lua["juce"].get_or_create<sol::table>();

    // juce_core
    juce_Array(table);
    juce_BigInteger(table);
    juce_File(table);
    juce_IPAddress(table);
    juce_Int(table);
    juce_MathConstants(table);
    juce_NormalisableRange(table);
    juce_Random(table);
    juce_Range(table);
    juce_Result(table);
    juce_StatisticsAccumulator(table);
    juce_String(table);
    juce_StringArray(table);
    juce_Uuid(table);
    juce_PerformanceCounter(table);
    juce_RelativeTime(table);
    juce_Time(table);

    // juce_events
    juce_Timer(table);

    // juce_graphics
    juce_AffineTransform(table);
    juce_Colour(table);
    juce_ColourGradient(table);
    juce_Colours(table);
    juce_Font(table);
    juce_Graphics(table);
    juce_Image(table);
    juce_ImageCache(table);
    juce_Justification(table);
    juce_Line(table);
    juce_Path(table);
    juce_Point(table);
    juce_Rectangle(table);

    // juce_gui_basics
    juce_Button(table);
    juce_ComboBox(table);
    juce_Component(table);
    juce_Grid(table);
    juce_Label(table);
    juce_ListBox(table);
    juce_ListBoxModel(table);
    juce_LookAndFeel(table);
    juce_LookAndFeel_V4(table);
    juce_MouseEvent(table);
    juce_TextButton(table);
    juce_Slider(table);

    // xtensions
    juce_LuaComponent(table);
    juce_LuaLookAndFeel_V4(table);
    juce_LuaTimer(table);
}
