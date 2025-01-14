cmake_minimum_required(VERSION 3.21)
project(jml-dev VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()
include(CTest)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/mc-juce/cmake)
include(mcConan)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY "https://github.com/juce-framework/JUCE" GIT_TAG "develop")
FetchContent_MakeAvailable(JUCE)
juce_disable_default_flags()

add_subdirectory(3rd_party/mc-juce/modules EXCLUDE_FROM_ALL)
add_subdirectory(modules)
add_subdirectory(tool/jml-cli)
add_subdirectory(tool/jml-designer)
add_subdirectory(tool/jml-gui-tester)
add_subdirectory(tool/jml-viewer)
add_subdirectory(test)
