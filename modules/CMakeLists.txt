project(lua-juce VERSION 0.1.0)

find_package(sol2 REQUIRED)

juce_add_modules(ALIAS_NAMESPACE mc
    lua_juce_core
    lua_juce_events
    lua_juce_graphics
    lua_juce_gui_basics
)
