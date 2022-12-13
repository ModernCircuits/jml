cmake_minimum_required(VERSION 3.21)
project(jml-cli VERSION 0.1.0)

find_package(CLI11 REQUIRED)
find_package(sol2 REQUIRED)

juce_add_console_app(jml-cli
    PRODUCT_NAME
        "jml-cli"
)

target_sources(jml-cli
    PRIVATE
        "Main.cpp"

        "JmlCommandline.cpp"
        "JmlCommandline.hpp"

        "Command/Snapshot.hpp"
        "Command/Test.hpp"
)

target_include_directories(jml-cli
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_compile_definitions(jml-cli
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

target_link_libraries(jml-cli
    PRIVATE
        mc::lua_juce_bindings

    PUBLIC
        lua::lua
        sol2::sol2
        CLI11::CLI11

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
