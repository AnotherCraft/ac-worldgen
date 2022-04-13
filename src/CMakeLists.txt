# Speedup tips:
# - use jom instead of make -> parallel builds

cmake_minimum_required(VERSION 3.20)

project(ac_client VERSION 0.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BASE_DIR "${CMAKE_BINARY_DIR}/../../..")
set(PROJECT_BASE_DIR "${PROJECT_SOURCE_DIR}/..")

include(../platform_config.cmake)

# ===========================================
# Qt
# ===========================================
set(QT_USE_OPENGL ON)
find_package(Qt6 COMPONENTS Widgets Qml Gui OpenGL Quick Concurrent QuickControls2 ShaderTools REQUIRED CONFIG)

# ===========================================
# Executable
# ===========================================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(ac_client WIN32)

target_compile_definitions(ac_client PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060200)
target_link_libraries(ac_client PRIVATE Qt6::Widgets Qt6::Qml Qt6::Gui Qt6::OpenGL Qt6::Quick Qt6::Concurrent Qt6::QuickControls2)

# ===========================================
# WASMER
# ===========================================
target_include_directories(ac_client SYSTEM PRIVATE "${WASMER_DIR}/include")
find_library(wasmer_lib NAMES wasmer PATHS "${WASMER_DIR}/lib" REQUIRED)
target_link_libraries(ac_client PRIVATE ${wasmer_lib})

# Without this, it would push dllimport declspec
target_compile_definitions(ac_client PRIVATE "WASM_API_EXTERN=")

if (WIN32)
    target_link_libraries(ac_client PRIVATE bcrypt)
endif ()

# ===========================================
# OpenFBX
# ===========================================
target_include_directories(ac_client PRIVATE "${PROJECT_BASE_DIR}/deps/openfbx/src")
file(GLOB_RECURSE ofbx_src CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/deps/openfbx/src/*.cpp" "${PROJECT_BASE_DIR}/deps/openfbx/src/*.c")
set_source_files_properties(${ofbx_src} PROPERTIES LANGUAGE CXX) # Gotta do this, otherwise cmake is silently ignoring .c files for CXX project
target_sources(ac_client PRIVATE ${ofbx_src})

# ===========================================
# YAML-CPP
# ===========================================
find_package(yaml-cpp PATHS "${CMAKE_BASE_DIR}/install/yamlcpp/share/cmake" REQUIRED)
target_link_libraries(ac_client PRIVATE yaml-cpp)

# ===========================================
# Tracy
# ===========================================
target_include_directories(ac_client SYSTEM PRIVATE "${PROJECT_BASE_DIR}/deps/tracy")
target_compile_definitions(ac_client PRIVATE TRACY_ENABLE)
target_compile_definitions(ac_client PRIVATE TRACY_ON_DEMAND)
find_library(tracy_lib NAMES tracyclient PATHS "${CMAKE_BASE_DIR}/tracy-prefix/src/tracy-build" REQUIRED)
target_link_libraries(ac_client PRIVATE "${tracy_lib}")

# ===========================================
# Antlr
# ===========================================
target_include_directories(ac_client SYSTEM PRIVATE "${CMAKE_BASE_DIR}/install/antlr/include")

# Antlr headers get screwed up by the "emit" macro from Qt includes, so we have to disable precompiled headers for woglac files
file(GLOB_RECURSE ac_client_woglac_src CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/src/server/world/worldgen/woglac/*.cpp")
set_source_files_properties(${ac_client_woglac_src} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

find_library(antlr_lib NAMES antlr4-runtime-static PATHS "${CMAKE_BASE_DIR}/install/antlr/lib" REQUIRED)
target_link_libraries(ac_client PRIVATE "${antlr_lib}")
target_compile_definitions(ac_client PRIVATE ANTLR4CPP_STATIC)

# ===========================================
# OpenXR
# ===========================================
find_package(openxr PATHS "${CMAKE_BASE_DIR}/install/openxr" REQUIRED)
target_link_libraries(ac_client PRIVATE OpenXR::openxr_loader OpenXR::headers)

find_library(opengl_lib NAMES opengl32 REQUIRED)
target_link_libraries(ac_client PRIVATE ${opengl_lib})

# ===========================================
# Soloud
# ===========================================
target_include_directories(ac_client SYSTEM PRIVATE "${PROJECT_BASE_DIR}/deps/soloud/include")

file(
        GLOB_RECURSE soloud_src CONFIGURE_DEPENDS
        "${PROJECT_BASE_DIR}/deps/soloud/src/core/*.cpp"
        "${PROJECT_BASE_DIR}/deps/soloud/src/filter/*.cpp"
        "${PROJECT_BASE_DIR}/deps/soloud/src/audiosource/wav/*.cpp"
        "${PROJECT_BASE_DIR}/deps/soloud/src/audiosource/wav/*.c"
        "${PROJECT_BASE_DIR}/deps/soloud/src/backend/miniaudio/*.cpp"
)

set_source_files_properties(${soloud_src} PROPERTIES LANGUAGE CXX) # Gotta do this, otherwise cmake is silently ignoring .c files for CXX project
target_sources(ac_client PRIVATE ${soloud_src})
target_compile_definitions(ac_client PRIVATE "WITH_MINIAUDIO")

# ===========================================
# Project config
# ===========================================
set(PROGRAM_NAME AnotherCraft)

target_compile_definitions(ac_client PRIVATE
        "PROGRAM_VERSION=\"${CMAKE_PROJECT_VERSION}\""
        "PROGRAM_NAME_VERSION=\"${PROGRAM_NAME} ${CMAKE_PROJECT_VERSION}\""
        "PLATFORM_ID=\"${OS_STRING}_${PLATFORM_STRING}\""
        )

# ===========================================
# Sources & includes
# ===========================================
file(
        GLOB_RECURSE ac_client_src CONFIGURE_DEPENDS
        "${PROJECT_BASE_DIR}/src/*.cc"
        "${PROJECT_BASE_DIR}/src/*.cpp"
)

target_sources(ac_client PRIVATE ${ac_client_src})

target_include_directories(ac_client PRIVATE "${PROJECT_BASE_DIR}/src")
target_include_directories(ac_client SYSTEM PRIVATE "${PROJECT_BASE_DIR}/include")

if (1)
    target_precompile_headers(
            ac_client PRIVATE
            "${PROJECT_BASE_DIR}/src/common/declares.h"
            "${PROJECT_BASE_DIR}/src/common/defines.h"
            "${PROJECT_BASE_DIR}/src/client/declares.h"
            "${PROJECT_BASE_DIR}/src/server/declares.h"
    )
endif ()

# ===========================================
# Resources
# ===========================================
file(GLOB_RECURSE qml_files CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/qml/*")
qt_add_resources(ac_client "qml"
        PREFIX "/qml"
        BASE "${PROJECT_BASE_DIR}/qml"
        FILES ${qml_files}
        )

file(GLOB_RECURSE res_files CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/res/*")
qt_add_resources(ac_client "res"
        PREFIX "/res"
        BASE "${PROJECT_BASE_DIR}/res"
        FILES ${res_files}
        )

file(GLOB_RECURSE qml_shader_files CONFIGURE_DEPENDS "${PROJECT_BASE_DIR}/qml/*.frag" "${PROJECT_BASE_DIR}/qml/*.vert")
qt_add_shaders(ac_client "qml_shaders"
        PREFIX "/qml"
        BASE "${PROJECT_BASE_DIR}/qml"
        FILES ${qml_shader_files}
        )

if (MSVC)
    target_compile_options(ac_client PRIVATE /Zf /MP)

    # Getting warning conflicting use
    target_link_options(ac_client PRIVATE /NODEFAULTLIB:LIBCMT)
endif ()

# ===========================================
# Deployment
# ===========================================
get_target_property(QMAKE_FILEPATH Qt6::qmake IMPORTED_LOCATION)

install(CODE "set(ac_client_target_file \"$<TARGET_FILE:ac_client>\")")
install(CODE "set(QMAKE_FILEPATH \"${QMAKE_FILEPATH}\")")
install(CODE "set(PROJECT_SOURCE_DIR \"${PROJECT_BASE_DIR}\")")
install(CODE "set(CMAKE_BINARY_DIR \"${CMAKE_BASE_DIR}\")")
install(SCRIPT "${PROJECT_BASE_DIR}/deploy.cmake")