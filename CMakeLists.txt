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
        "src/Main.cpp"
        "src/MainComponent.h"
        "src/MainComponent.cpp"

        "src/Bindings/Juce.cpp"
        "src/Bindings/Juce.hpp"

        "src/Bindings/juce_core/BigInteger.cpp"
        "src/Bindings/juce_core/BigInteger.hpp"
        "src/Bindings/juce_core/File.hpp"
        "src/Bindings/juce_core/File.cpp"
        "src/Bindings/juce_core/Int.hpp"
        "src/Bindings/juce_core/Int.cpp"
        "src/Bindings/juce_core/IPAddress.hpp"
        "src/Bindings/juce_core/IPAddress.cpp"
        "src/Bindings/juce_core/MathConstants.hpp"
        "src/Bindings/juce_core/MathConstants.cpp"
        "src/Bindings/juce_core/NormalisableRange.hpp"
        "src/Bindings/juce_core/NormalisableRange.cpp"
        "src/Bindings/juce_core/Random.cpp"
        "src/Bindings/juce_core/Random.hpp"
        "src/Bindings/juce_core/Range.cpp"
        "src/Bindings/juce_core/Range.hpp"
        "src/Bindings/juce_core/Result.cpp"
        "src/Bindings/juce_core/Result.hpp"
        "src/Bindings/juce_core/StatisticsAccumulator.cpp"
        "src/Bindings/juce_core/StatisticsAccumulator.hpp"
        "src/Bindings/juce_core/String.cpp"
        "src/Bindings/juce_core/String.hpp"
        "src/Bindings/juce_core/Uuid.cpp"
        "src/Bindings/juce_core/Uuid.hpp"

        "src/Bindings/juce_events/Timer.cpp"
        "src/Bindings/juce_events/Timer.hpp"

        "src/Bindings/juce_graphics/AffineTransform.cpp"
        "src/Bindings/juce_graphics/AffineTransform.hpp"
        "src/Bindings/juce_graphics/Colour.cpp"
        "src/Bindings/juce_graphics/Colour.hpp"
        "src/Bindings/juce_graphics/ColourGradient.cpp"
        "src/Bindings/juce_graphics/ColourGradient.hpp"
        "src/Bindings/juce_graphics/Colours.cpp"
        "src/Bindings/juce_graphics/Colours.hpp"
        "src/Bindings/juce_graphics/Graphics.cpp"
        "src/Bindings/juce_graphics/Graphics.hpp"
        "src/Bindings/juce_graphics/Line.cpp"
        "src/Bindings/juce_graphics/Line.hpp"
        "src/Bindings/juce_graphics/Path.cpp"
        "src/Bindings/juce_graphics/Path.hpp"
        "src/Bindings/juce_graphics/Point.cpp"
        "src/Bindings/juce_graphics/Point.hpp"
        "src/Bindings/juce_graphics/Rectangle.cpp"
        "src/Bindings/juce_graphics/Rectangle.hpp"

        "src/Bindings/juce_gui_basics/Component.cpp"
        "src/Bindings/juce_gui_basics/Component.hpp"
        "src/Bindings/juce_gui_basics/Label.cpp"
        "src/Bindings/juce_gui_basics/Label.hpp"
        "src/Bindings/juce_gui_basics/LookAndFeel_V4.cpp"
        "src/Bindings/juce_gui_basics/LookAndFeel_V4.hpp"
        "src/Bindings/juce_gui_basics/LookAndFeel.cpp"
        "src/Bindings/juce_gui_basics/LookAndFeel.hpp"
        "src/Bindings/juce_gui_basics/MouseEvent.cpp"
        "src/Bindings/juce_gui_basics/MouseEvent.hpp"
        "src/Bindings/juce_gui_basics/MouseWheelDetails.cpp"
        "src/Bindings/juce_gui_basics/MouseWheelDetails.hpp"
        "src/Bindings/juce_gui_basics/Slider.cpp"
        "src/Bindings/juce_gui_basics/Slider.hpp"
        "src/Bindings/juce_gui_basics/TextButton.cpp"
        "src/Bindings/juce_gui_basics/TextButton.hpp"

        "src/Bindings/juce_xtensions/LuaComponent.cpp"
        "src/Bindings/juce_xtensions/LuaComponent.hpp"
        "src/Bindings/juce_xtensions/LuaTimer.cpp"
        "src/Bindings/juce_xtensions/LuaTimer.hpp"
)

target_include_directories(JuceLuaTest
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
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
