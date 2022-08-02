# Speedup tips:
# - use jom instead of make -> parallel builds

cmake_minimum_required(VERSION 3.20)

set(target ac_worldgen)
project(${target} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
target_include_directories(${target} SYSTEM PRIVATE "${PROJECT_BASE_DIR}/deps/tracy")
target_compile_definitions(${target} PRIVATE TRACY_ENABLE)
target_compile_definitions(${target} PRIVATE TRACY_ON_DEMAND)
find_library(tracy_lib NAMES tracyclient PATHS "${CMAKE_BASE_DIR}/tracy-prefix/src/tracy-build" "${CMAKE_BASE_DIR}/tracy-prefix/src/tracy-build/Debug" REQUIRED)
target_link_libraries(${target} PRIVATE "${tracy_lib}")

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