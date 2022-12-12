project(jml-viewer VERSION 0.1.0)

find_package(sol2 REQUIRED)

juce_add_gui_app(jml-viewer
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "JML Viewer"           # The name of the final executable, which can differ from the target name
)

target_sources(jml-viewer
    PRIVATE
        "jml-viewer/Application/CommandIDs.hpp"
        "jml-viewer/Application/Main.cpp"
        "jml-viewer/Application/MainComponent.hpp"
        "jml-viewer/Application/MainComponent.cpp"
        "jml-viewer/Application/MenuBar.hpp"
        "jml-viewer/Application/MenuBar.cpp"

        "jml-viewer/CodeEditor/CodeEditor.cpp"
        "jml-viewer/CodeEditor/CodeEditor.hpp"

        "jml-viewer/LookAndFeel/JmlViewerColors.hpp"
        "jml-viewer/LookAndFeel/JmlViewerLookAndFeel.cpp"
        "jml-viewer/LookAndFeel/JmlViewerLookAndFeel.hpp"

        "jml-viewer/Lua/Juce.cpp"
        "jml-viewer/Lua/Juce.hpp"

        "jml-viewer/Preview/ComponentContainer.cpp"
        "jml-viewer/Preview/ComponentContainer.hpp"
        "jml-viewer/Preview/ComponentTree.cpp"
        "jml-viewer/Preview/ComponentTree.hpp"
        "jml-viewer/Preview/FileChangeListener.cpp"
        "jml-viewer/Preview/FileChangeListener.hpp"
        "jml-viewer/Preview/LuaScriptViewer.cpp"
        "jml-viewer/Preview/LuaScriptViewer.hpp"
)

target_include_directories(jml-viewer
    PUBLIC
        ${PROJECT_SOURCE_DIR}/jml-viewer
)

target_compile_definitions(jml-viewer
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-viewer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-viewer,JUCE_VERSION>"
)

target_link_libraries(jml-viewer
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
