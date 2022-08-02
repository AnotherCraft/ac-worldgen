# Speedup tips:
# - use jom instead of make -> parallel builds

cmake_minimum_required(VERSION 3.20)
include(ExternalProject)

project(ac_worldgen_master VERSION 0.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND EXTERNAL_ARGS
        -D "CMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
        -D "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
        -D "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}"

        -G "${CMAKE_GENERATOR}"
        )

set(CMAKE_BASE_DIR "${CMAKE_BINARY_DIR}")
set(PROJECT_BASE_DIR "${PROJECT_SOURCE_DIR}")

include(platform_config.cmake)

# ===========================================
# Tracy
# ===========================================
ExternalProject_Add(
        tracy
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/tracy"
        EXCLUDE_FROM_ALL ON
        CMAKE_ARGS ${EXTERNAL_ARGS}
        -D "CMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/install/tracy"
        -D TRACY_ENABLE=ON
        -D TRACY_ON_DEMAND=ON
)

# ===========================================
# Antlr
# ===========================================
ExternalProject_Add(
        antlr
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/antlr/runtime/Cpp"
        EXCLUDE_FROM_ALL ON

        TEST_COMMAND ""

        CMAKE_ARGS ${EXTERNAL_ARGS}
        -D WITH_STATIC_CRT=OFF
        -D "CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install/antlr"
)

# ===========================================
# FastNoise2
# ===========================================
ExternalProject_Add(
        fastNoise2
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/deps/fastNoise2"
        EXCLUDE_FROM_ALL ON

        TEST_COMMAND ""

        CMAKE_ARGS ${EXTERNAL_ARGS}
        -D FASTNOISE2_NOISETOOL=OFF
        -D FASTNOISE2_TESTS=OFF
        -D "CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install/fastNoise2"
)


# ===========================================
# Worldgen
# ===========================================
ExternalProject_Add(ac_worldgen_nodeploy
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/src"
        INSTALL_COMMAND ""
        EXCLUDE_FROM_ALL ON
        CMAKE_ARGS ${EXTERNAL_ARGS}
        )

ExternalProject_Add(ac_worldgen_deploy
        DEPENDS antlr tracy fastNoise2
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/src"
        INSTALL_COMMAND ""
        CMAKE_ARGS ${EXTERNAL_ARGS}
        )

# ===========================================
# Dummy target for intellisense
# ===========================================
add_executable(x_ac_worldgen_dummy WIN32 EXCLUDE_FROM_ALL)
file(
        GLOB_RECURSE ac_client_src CONFIGURE_DEPENDS
        "${PROJECT_BASE_DIR}/src/*.cc"
        "${PROJECT_BASE_DIR}/src/*.cpp"
        "${PROJECT_BASE_DIR}/src/*.h"
)
target_compile_definitions(x_ac_worldgen_dummy PRIVATE TRACY_ENABLE)
target_sources(x_ac_worldgen_dummy PRIVATE ${ac_client_src})
target_precompile_headers(x_ac_worldgen_dummy PRIVATE "${PROJECT_BASE_DIR}/src/pch.h")
target_include_directories(x_ac_worldgen_dummy PRIVATE "${PROJECT_BASE_DIR}/src")
target_include_directories(x_ac_worldgen_dummy SYSTEM PRIVATE
        "${PROJECT_BASE_DIR}/include"
        "${PROJECT_BASE_DIR}/deps/tracy"
        "${CMAKE_BASE_DIR}/install/antlr/include"
        "${CMAKE_BASE_DIR}/install/fastNoise2/include"
        )
