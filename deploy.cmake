# Is include in the main cmakelists on install

get_filename_component(target_directory "${ac_client_target_file}" DIRECTORY)

# Qt
if (1)
    message(STATUS "Deploying Qt...")

    get_filename_component(qt_bin_dir "${QMAKE_FILEPATH}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${qt_bin_dir}")

    execute_process(
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            "${ac_client_target_file}"
            "--qmldir" "${PROJECT_SOURCE_DIR}/qml"
            --qmldir "${PROJECT_SOURCE_DIR}/src"
            --compiler-runtime
    )
    message(STATUS "Qt deployed.")
endif ()

# Other DLLS
if (1)
    message(STATUS "Deploying 3rd party libraries...")
    file(
            GET_RUNTIME_DEPENDENCIES
            EXECUTABLES "${ac_client_target_file}"
            DIRECTORIES
            "${CMAKE_BINARY_DIR}/install/antlr/lib"
            "${WASMER_DIR}/lib"

            PRE_INCLUDE_REGEXES  "wasmer|antlr"
            PRE_EXCLUDE_REGEXES "."
            RESOLVED_DEPENDENCIES_VAR libs_found
    )
    file(COPY ${libs_found} DESTINATION "${target_directory}")
    message(STATUS "3rd party libraries deployed.")
endif ()