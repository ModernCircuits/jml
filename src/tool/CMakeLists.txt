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
    "LuaSuculenta/Main.cpp"
    "LuaSuculenta/MainComponent.h"
    "LuaSuculenta/MainComponent.cpp"

    "LuaSuculenta/CodeEditor.cpp"
    "LuaSuculenta/CodeEditor.hpp"
    "LuaSuculenta/ComponentContainer.hpp"
    "LuaSuculenta/ComponentTree.hpp"
    "LuaSuculenta/FileChangeListener.hpp"
    "LuaSuculenta/Juce.cpp"
    "LuaSuculenta/Juce.hpp"
    "LuaSuculenta/LuaPreview.cpp"
    "LuaSuculenta/LuaPreview.hpp"
    "LuaSuculenta/LuaSuculentaColors.hpp"
    "LuaSuculenta/LuaSuculentaLookAndFeel.cpp"
    "LuaSuculenta/LuaSuculentaLookAndFeel.hpp"
    "LuaSuculenta/MenuBar.hpp"
    "LuaSuculenta/MenuBar.cpp"
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
