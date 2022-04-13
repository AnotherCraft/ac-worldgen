if (WIN32)
    set(OS_STRING win)
elseif (UNIX)
    set(OS_STRING unix)
endif ()

if (CMAKE_SYSTEM_PROCESSOR MATCHES "(amd64)|(AMD64)")
    set(PLATFORM_STRING x86_64)
else ()
    set(PLATFORM_STRING x86)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_STRING _dbg)
else ()
    set(BUILD_TYPE_STRING)
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BASE_DIR}/../bin/bin_worldgen_${OS_STRING}_${PLATFORM_STRING}${BUILD_TYPE_STRING}")