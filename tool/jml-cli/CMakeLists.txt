cmake_minimum_required(VERSION 3.21)
project(jml-cli VERSION 0.1.0)

find_package(CLI11 REQUIRED)
find_package(sol2 REQUIRED)

juce_add_console_app(jml-cli
    PRODUCT_NAME
        "jml-cli"
)

set(sources
    "Main.cpp"

    "JmlCommandline.cpp"
    "JmlCommandline.hpp"

    "Command/Snapshot.hpp"
    "Command/Test.hpp"
)

target_sources(jml-cli PRIVATE ${sources})
set_source_files_properties(jml-cli ${sources} PROPERTIES UNITY_GROUP "src")
set_target_properties(jml-cli PROPERTIES UNITY_BUILD_MODE GROUP)

target_include_directories(jml-cli
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_compile_definitions(jml-cli
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING=1
)

target_link_libraries(jml-cli
    PRIVATE
        mc::mc_lua_juce

    PUBLIC
        lua::lua
        sol2::sol2
        CLI11::CLI11

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
