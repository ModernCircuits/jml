project(lua-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE mc
    mc_lua_juce_core
    mc_lua_juce_data_structures
    mc_lua_juce_events
    mc_lua_juce_graphics
    mc_lua_juce_gui_basics

    mc_lua_juce

    mc_gui_testing
)
