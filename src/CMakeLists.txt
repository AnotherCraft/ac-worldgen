# Speedup tips:
# - use jom instead of make -> parallel builds

cmake_minimum_required(VERSION 3.20)

set(target ac_worldgen)
project(${target} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Formatter requires c++latest for MSVC2019 and less
if (DEFINED MSVC_VERSION AND MSVC_VERSION LESS 1930)
    set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
    set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
endif()

set(CMAKE_BASE_DIR "${CMAKE_BINARY_DIR}/../../..")
set(PROJECT_BASE_DIR "${PROJECT_SOURCE_DIR}/..")

include(../platform_config.cmake)

# ===========================================
# Executable
# ===========================================
add_executable(${target})

target_compile_definitions(${target} PRIVATE _USE_MATH_DEFINES)

# ===========================================
# Tracy
# ===========================================
find_package(Threads REQUIRED) # Dependency of Tracy
find_package(tracy PATHS "${CMAKE_BASE_DIR}/install/tracy/share/Tracy" REQUIRED)
target_link_libraries(ac_worldgen PRIVATE Tracy::TracyClient)

# ===========================================
# FastNoise2
# ===========================================
target_include_directories(${target} SYSTEM PRIVATE "${CMAKE_BASE_DIR}/install/fastNoise2/include")
find_library(fastNoise2_lib NAMES FastNoise FastNoiseD PATHS "${CMAKE_BASE_DIR}/install/fastNoise2/lib" REQUIRED)
target_link_libraries(${target} PRIVATE "${fastNoise2_lib}")

# ===========================================
# Antlr
# ===========================================
target_include_directories(${target} SYSTEM PRIVATE "${CMAKE_BASE_DIR}/install/antlr/include")

find_library(antlr_lib NAMES antlr4-runtime-static PATHS "${CMAKE_BASE_DIR}/install/antlr/lib" REQUIRED)
target_link_libraries(${target} PRIVATE "${antlr_lib}")
target_compile_definitions(${target} PRIVATE ANTLR4CPP_STATIC)

# ===========================================
# Sources & includes
# ===========================================
file(
        GLOB_RECURSE source_files CONFIGURE_DEPENDS
        "${PROJECT_BASE_DIR}/src/*.cc"
        "${PROJECT_BASE_DIR}/src/*.cpp"
)

target_sources(${target} PRIVATE ${source_files})

target_include_directories(${target} PRIVATE "${PROJECT_BASE_DIR}/src")
target_include_directories(${target} SYSTEM PRIVATE "${PROJECT_BASE_DIR}/include")
target_precompile_headers(${target} PRIVATE "${PROJECT_BASE_DIR}/src/pch.h")

# ===========================================
# Resources
# ===========================================
if (MSVC)
    target_compile_options(${target} PRIVATE /Zf /MP /bigobj)

    # Getting warning conflicting use
    target_link_options(${target} PRIVATE /NODEFAULTLIB:LIBCMT)
endif ()