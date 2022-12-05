project(lua-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE mc
    lua_juce_sol2

    lua_juce_core
    lua_juce_events
    lua_juce_graphics
    lua_juce_gui_basics
)
