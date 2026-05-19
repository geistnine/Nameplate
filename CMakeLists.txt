cmake_minimum_required(VERSION 4.2.1)

project(Nameplate
    VERSION 0.60
    LANGUAGES CXX
    DESCRIPTION "Corrects defects in nameplate rendering."
    HOMEPAGE_URL "https://www.github.com/Shirk/Nameplate"
)

# set(ASHITA_SDK_PATH "../Ashita v4 SDK 4.11/plugins/sdk" CACHE STRING "Ashita SDK Path")
# set(ASHITA_SDK_PATH "../Ashita v4 SDK 4.14/plugins/sdk" CACHE STRING "Ashita SDK Path")
# set(ASHITA_SDK_PATH "../Ashita v4 SDK 4.15/plugins/sdk" CACHE STRING "Ashita SDK Path")
# set(ASHITA_SDK_PATH "../Ashita v4 SDK 4.16/plugins/sdk" CACHE STRING "Ashita SDK Path")
# set(ASHITA_SDK_PATH "../Ashita v4 SDK 4.30/plugins/sdk" CACHE STRING "Ashita SDK Path")
set(ASHITA_SDK_PATH "sdk" CACHE STRING "Ashita SDK Path (override with -DASHITA_SDK_PATH=...)")
message(STATUS "ASHITA_SDK_PATH=${ASHITA_SDK_PATH}")

# Plugin environment:
# ASHITA_V3
# ASHITA_V4 (also includes Windozer) (default)
set(TARGET_PLATFORMS "ASHITA_V3" "ASHITA_V4")
set(TARGET_PLATFORM "ASHITA_V4" CACHE STRING "Target Plugin Platform")
set_property(CACHE TARGET_PLATFORM PROPERTY STRINGS TARGET_PLATFORMS)

if(NOT TARGET_PLATFORM IN_LIST TARGET_PLATFORMS)
    message(FATAL_ERROR "TARGET_PLATFORM \"${TARGET_PLATFORM}\" is not supported. TARGET_PLATFORM must be one of: ${TARGET_PLATFORMS}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/versioninfo.rc.in versioninfo.rc @ONLY)

add_library(Nameplate SHARED)

set_target_properties(Nameplate PROPERTIES
  C_STANDARD 23
  C_STANDARD_REQUIRED True
  C_EXTENSIONS OFF
  CXX_STANDARD 26
  CXX_STANDARD_REQUIRED True
  CXX_EXTENSIONS OFF
)

target_sources(Nameplate PRIVATE
    src/Nameplate.cpp
    src/Nameplate.h

    "${CMAKE_CURRENT_BINARY_DIR}/versioninfo.rc"

    PRIVATE FILE_SET CXX_MODULES FILES
    src/findsignature.cppm)

if(TARGET_PLATFORM STREQUAL "ASHITA_V4")
    target_sources(Nameplate PRIVATE
        src/Ashita/Ashita.cpp
        src/Ashita/exports.h

        src/Windozer/Windozer.cpp
        src/Windozer/Windozer.h

        src/exports.def)
elseif(TARGET_PLATFORM STREQUAL "ASHITA_V3")
    target_sources(Nameplate PRIVATE
        src/Ashita-v3/Ashita.cpp
        src/Ashita-v3/exports.h

        src/Ashita-v3/exports.def)
endif()

target_include_directories(Nameplate PRIVATE ${ASHITA_SDK_PATH})
target_compile_definitions(Nameplate PRIVATE WIN32_LEAN_AND_MEAN)
set_target_properties(Nameplate PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
set_target_properties(Nameplate PROPERTIES INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE)

if(MSVC)
    target_compile_options(Nameplate PRIVATE /EHa /W4)
else()
    target_compile_options(Nameplate PRIVATE
        -m32
        -fno-rtti -march=nehalem -fomit-frame-pointer -ffast-math -mfpmath=sse -mtune=skylake
        -Wall -Wextra -Wpedantic -W
        -Wno-c++98-compat -Wno-reserved-macro-identifier -Wno-nonportable-system-include-path
        -Wno-reserved-identifier -Wno-gnu-anonymous-struct -Wno-nested-anon-types
        -Wno-c++98-compat-pedantic -Wno-non-virtual-dtor -Wno-extra-semi -Wno-shadow-field
        -Wno-old-style-cast -Wno-float-equal -Wno-documentation -Wno-microsoft-end-of-file
        -Wno-sign-conversion -Wno-cast-align
        -Wno-newline-eof -Wno-language-extension-token -Wno-cast-qual -Wno-extra-semi-stmt
        -Wno-deprecated-copy-with-user-provided-dtor -Wno-missing-noreturn
        -Wno-tautological-unsigned-zero-compare -Wno-duplicate-enum -Wno-double-promotion
        -Wno-documentation-unknown-command -Wno-unused-function
        -Wno-c99-extensions -Wno-missing-braces)
    target_link_options(Nameplate PRIVATE -m32)
endif()
