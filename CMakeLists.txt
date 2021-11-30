cmake_minimum_required(VERSION 3.15)
project(GUI_APP_EXAMPLE VERSION 0.0.1)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(mcConan)

find_package(sol2 REQUIRED)
add_subdirectory(3rd_party/JUCE)

juce_add_gui_app(JuceLuaTest
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "JUCE Lua"             # The name of the final executable, which can differ from the target name
)

target_sources(JuceLuaTest
    PRIVATE
        src/Main.cpp
        src/MainComponent.h
        src/MainComponent.cpp
)

target_compile_definitions(JuceLuaTest
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:JuceLuaTest,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:JuceLuaTest,JUCE_VERSION>"
)

target_link_libraries(JuceLuaTest
    PRIVATE
        juce::juce_gui_extra
    PUBLIC
        lua::lua
        sol2::sol2
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)
