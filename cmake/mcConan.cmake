if(CONAN_EXPORTED)
    # standard conan installation, deps will be defined in conanfile.py
    # and not necessary to call conan again, conan is already running
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(
            DOWNLOAD
                "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY
                ON
        )
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_add_remote(NAME conancenter       INDEX 0 URL https://center.conan.io)
    conan_cmake_autodetect(settings)
    conan_cmake_install(
        CONANFILE
            conanfile.txt
        PATH_OR_REFERENCE
            ${CMAKE_CURRENT_SOURCE_DIR}
        BUILD
            missing
        SETTINGS
            ${settings}
    )
endif()