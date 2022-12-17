project(jml-gui-tester VERSION 0.1.0)

find_package(mc-core REQUIRED)
find_package(sol2 REQUIRED)

juce_add_gui_app(jml-gui-tester
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "JML GUI Tester"       # The name of the final executable, which can differ from the target name
)

set(sources
    "Application/Main.cpp"
    "Application/MainComponent.hpp"
    "Application/MainComponent.cpp"
)

target_sources(jml-gui-tester PRIVATE ${sources})
set_source_files_properties(jml-gui-tester ${sources} PROPERTIES UNITY_GROUP "src")
set_target_properties(jml-gui-tester PROPERTIES UNITY_BUILD_MODE GROUP)

target_include_directories(jml-gui-tester
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_compile_definitions(jml-gui-tester
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-gui-tester,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-gui-tester,JUCE_VERSION>"
)

target_link_libraries(jml-gui-tester
    PRIVATE
        mc::lua_juce_bindings
        mc::mc_gui_testing
        mc::mc_gui_extra

    PUBLIC
        lua::lua
        sol2::sol2
        mc-core::mc-core

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
