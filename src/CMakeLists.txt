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
# Qt
# ===========================================
find_package(Qt6 COMPONENTS Concurrent REQUIRED CONFIG)

# ===========================================
# Executable
# ===========================================
set(CMAKE_AUTOMOC ON)

qt_add_executable(${target})

target_compile_definitions(${target} PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060200)
target_link_libraries(${target} PRIVATE Qt6::Concurrent)

# ===========================================
# Tracy
# ===========================================
target_include_directories(${target} SYSTEM PRIVATE "${PROJECT_BASE_DIR}/deps/tracy")
target_compile_definitions(${target} PRIVATE TRACY_ENABLE)
target_compile_definitions(${target} PRIVATE TRACY_ON_DEMAND)
find_library(tracy_lib NAMES tracyclient PATHS "${CMAKE_BASE_DIR}/tracy-prefix/src/tracy-build" REQUIRED)
target_link_libraries(${target} PRIVATE "${tracy_lib}")

# ===========================================
# Antlr
# ===========================================
target_include_directories(${target} SYSTEM PRIVATE "${CMAKE_BASE_DIR}/install/antlr/include")

# Antlr headers get screwed up by the "emit" macro from Qt includes, so we have to disable precompiled headers for woglac files
file(GLOB_RECURSE woglac_src CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/src/woglac/*.cpp")
set_source_files_properties(${woglac_src} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

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
    target_compile_options(${target} PRIVATE /Zf /MP $<$<CONFIG:RELEASE>:/O3>)

    # Getting warning conflicting use
    target_link_options(${target} PRIVATE /NODEFAULTLIB:LIBCMT)
endif ()

# ===========================================
# Deployment
# ===========================================
get_target_property(QMAKE_FILEPATH Qt6::qmake IMPORTED_LOCATION)

install(CODE "set(target_file \"$<TARGET_FILE:${target}>\")")
install(CODE "set(QMAKE_FILEPATH \"${QMAKE_FILEPATH}\")")
install(CODE "set(PROJECT_SOURCE_DIR \"${PROJECT_BASE_DIR}\")")
install(CODE "set(CMAKE_BINARY_DIR \"${CMAKE_BASE_DIR}\")")
install(SCRIPT "${PROJECT_BASE_DIR}/deploy.cmake")