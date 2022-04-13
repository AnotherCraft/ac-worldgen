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
        INSTALL_COMMAND "" # Does not have install target
        CMAKE_ARGS ${EXTERNAL_ARGS}
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
        -D "MSVC_RUNTIME_LIBRARY=MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

# ===========================================
# Worldgen
# ===========================================
ExternalProject_Add(x_ac_worldgen
        SOURCE_DIR "${PROJECT_SOURCE_DIR}/src"
        BUILD_ALWAYS ON
        STEP_TARGETS build
        CMAKE_ARGS ${EXTERNAL_ARGS}
        -D "WASMER_DIR=$ENV{WASMER_DIR}"
        )

add_custom_target(ac_worldgen_nodeploy DEPENDS x_ac_worldgen-build)
add_custom_target(ac_worldgen_deploy ALL DEPENDS openxr antlr tracy yamlcpp x_ac_worldgen)

# ===========================================
# Dummy target for intellisense
# ===========================================
set(QT_USE_OPENGL ON)
find_package(Qt6 COMPONENTS Widgets Qml Gui OpenGL Quick Concurrent QuickControls2 ShaderTools REQUIRED CONFIG)
qt_add_executable(x_ac_worldgen_dummy WIN32 EXCLUDE_FROM_ALL)
get_target_property(qtcore_binlocation Qt6::Core LOCATION)
get_filename_component(qtcore_location ${qtcore_binlocation} DIRECTORY)
set(qt_include_location "${qtcore_location}/../include")
target_include_directories(x_ac_worldgen_dummy PRIVATE
        "${qt_include_location}/QtWidgets"
        "${qt_include_location}/QtQml"
        "${qt_include_location}/QtQuick"
        "${qt_include_location}/QtQuickWidgets"
        "${qt_include_location}/QtQuickControls2"
        "${qt_include_location}/QtGui"
        "${qt_include_location}/QtOpenGL"
        "${qt_include_location}/QtConcurrent"
        )
target_compile_definitions(x_ac_worldgen_dummy PRIVATE
        "PROGRAM_VERSION=\"XX\""
        "PROGRAM_NAME_VERSION=\"XX\""
        "PLATFORM_ID=\"${OS_STRING}_${PLATFORM_STRING}\""
        )
file(
        GLOB_RECURSE ac_client_src CONFIGURE_DEPENDS
        "${PROJECT_BASE_DIR}/src/*.cc"
        "${PROJECT_BASE_DIR}/src/*.cpp"
        "${PROJECT_BASE_DIR}/src/*.h"
)
target_compile_definitions(x_ac_worldgen_dummy PRIVATE TRACY_ENABLE)
target_sources(x_ac_worldgen_dummy PRIVATE ${ac_client_src})
target_sources(x_ac_worldgen_dummy PRIVATE "${PROJECT_BASE_DIR}/qt6.natvis")
target_include_directories(x_ac_worldgen_dummy PRIVATE "${PROJECT_BASE_DIR}/src")
target_include_directories(x_ac_worldgen_dummy SYSTEM PRIVATE
        "${PROJECT_BASE_DIR}/include"
        "${PROJECT_BASE_DIR}/deps/tracy"
        "${PROJECT_BASE_DIR}/deps/openfbx/src"
        "${PROJECT_BASE_DIR}/deps/soloud/include"
        "${CMAKE_BASE_DIR}/install/yamlcpp/include"
        "${CMAKE_BASE_DIR}/install/openxr/include"
        "$ENV{WASMER_DIR}/include"
        )
