project(LuaSuculenta VERSION 0.1.0)

find_package(sol2 REQUIRED)

juce_add_gui_app(LuaSuculenta
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "Lua Suculenta"        # The name of the final executable, which can differ from the target name
)

target_sources(LuaSuculenta
    PRIVATE
        "LuaSuculenta/Application/CommandIDs.hpp"
        "LuaSuculenta/Application/Main.cpp"
        "LuaSuculenta/Application/MainComponent.hpp"
        "LuaSuculenta/Application/MainComponent.cpp"
        "LuaSuculenta/Application/MenuBar.hpp"
        "LuaSuculenta/Application/MenuBar.cpp"

        "LuaSuculenta/CodeEditor/CodeEditor.cpp"
        "LuaSuculenta/CodeEditor/CodeEditor.hpp"

        "LuaSuculenta/LookAndFeel/LuaSuculentaColors.hpp"
        "LuaSuculenta/LookAndFeel/LuaSuculentaLookAndFeel.cpp"
        "LuaSuculenta/LookAndFeel/LuaSuculentaLookAndFeel.hpp"

        "LuaSuculenta/Lua/Juce.cpp"
        "LuaSuculenta/Lua/Juce.hpp"

        "LuaSuculenta/Preview/ComponentContainer.hpp"
        "LuaSuculenta/Preview/ComponentTree.hpp"
        "LuaSuculenta/Preview/FileChangeListener.hpp"
        "LuaSuculenta/Preview/LuaPreview.cpp"
        "LuaSuculenta/Preview/LuaPreview.hpp"
)

target_include_directories(LuaSuculenta
    PUBLIC
        ${PROJECT_SOURCE_DIR}/LuaSuculenta
)

target_compile_definitions(LuaSuculenta
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:LuaSuculenta,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:LuaSuculenta,JUCE_VERSION>"
)

target_link_libraries(LuaSuculenta
    PRIVATE
        mc::lua_juce_core
        mc::lua_juce_events
        mc::lua_juce_graphics
        mc::lua_juce_gui_basics

        juce::juce_gui_extra

    PUBLIC
        lua::lua
        sol2::sol2
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
