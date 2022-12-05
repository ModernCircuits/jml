cmake_minimum_required(VERSION 3.15)
project(GUI_APP_EXAMPLE VERSION 0.0.1)

enable_testing()
include(CTest)

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

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY "https://github.com/juce-framework/JUCE" GIT_TAG "7.0.2")
FetchContent_MakeAvailable(JUCE)
juce_disable_default_flags()

find_package(sol2 REQUIRED)

add_subdirectory(src/Bindings)

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
        "src/LuaSuculenta/Main.cpp"
        "src/LuaSuculenta/MainComponent.h"
        "src/LuaSuculenta/MainComponent.cpp"

        "src/LuaSuculenta/CodeEditor.cpp"
        "src/LuaSuculenta/CodeEditor.hpp"
        "src/LuaSuculenta/ComponentContainer.hpp"
        "src/LuaSuculenta/ComponentTree.hpp"
        "src/LuaSuculenta/FileChangeListener.hpp"
        "src/LuaSuculenta/Juce.cpp"
        "src/LuaSuculenta/Juce.hpp"
        "src/LuaSuculenta/LuaPreview.cpp"
        "src/LuaSuculenta/LuaPreview.hpp"
        "src/LuaSuculenta/LuaSuculentaColors.hpp"
        "src/LuaSuculenta/LuaSuculentaLookAndFeel.cpp"
        "src/LuaSuculenta/LuaSuculentaLookAndFeel.hpp"
        "src/LuaSuculenta/MenuBar.hpp"
        "src/LuaSuculenta/MenuBar.cpp"
)

target_include_directories(LuaSuculenta
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
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
