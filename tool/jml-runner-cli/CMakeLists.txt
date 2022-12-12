cmake_minimum_required(VERSION 3.21)
project(jml-runner-cli VERSION 0.1.0)

find_package(sol2 REQUIRED)

juce_add_console_app(jml-runner-cli
    PRODUCT_NAME
        "jml-runner-cli"
)

target_sources(jml-runner-cli
    PRIVATE
        Main.cpp
)

target_compile_definitions(jml-runner-cli
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

target_link_libraries(jml-runner-cli
    PRIVATE
        mc::lua_juce_bindings

    PUBLIC
        lua::lua
        sol2::sol2

        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
