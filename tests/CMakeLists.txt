enable_testing()

SET(GENERATOR "${CMAKE_BINARY_DIR}/rust_qt_binding_generator/rust_qt_binding_generator")

add_custom_target("clean-rust")

function(rust_test NAME DIRECTORY)
    set(SRC "${CMAKE_CURRENT_SOURCE_DIR}")
    set(DIR "${SRC}/${DIRECTORY}")

    add_custom_command(
        OUTPUT "${DIR}/src/interface.rs"
               "${DIR}/src/implementation.rs"
               "${DIR}/src/types.rs"
               "${SRC}/${NAME}_rust.h"
        # if the cpp file is marked GENERATED, CMake will not check it for moc
        #      "${SRC}/${NAME}_rust.cpp"
        COMMAND "${GENERATOR}" --overwrite-implementation "${SRC}/${NAME}.json"
        MAIN_DEPENDENCY "${NAME}.json"
        DEPENDS "${GENERATOR}"
    )

    add_custom_command(
        OUTPUT "${DIR}/${RUST_TARGET_DIR}/librust.a"
        COMMAND cargo build ${RUST_BUILD_FLAG}
        DEPENDS "${DIR}/src/lib.rs"
                "${DIR}/src/implementation.rs"
                "${DIR}/src/interface.rs"
                "${DIR}/src/types.rs"
        WORKING_DIRECTORY "${DIR}"
    )
    add_custom_target("test_${DIRECTORY}"
        DEPENDS "${DIR}/${RUST_TARGET_DIR}/librust.a")

    add_executable("${NAME}" "${NAME}.cpp" "${NAME}_rust.cpp" "${NAME}_rust.h")
    add_dependencies("${NAME}" "test_${DIRECTORY}")
    target_link_libraries("${NAME}"
        Qt5::Core
        Qt5::Test
        "${DIR}/${RUST_TARGET_DIR}/librust.a"
    )
    set_property(TARGET ${NAME}
        APPEND PROPERTY AUTOGEN_TARGET_DEPENDS "${SRC}/${NAME}_rust.h"
        APPEND PROPERTY AUTOGEN_TARGET_DEPENDS "${SRC}/${NAME}_rust.cpp")

    add_test("build_${NAME}"
            "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target "${NAME}")
    add_test("${NAME}" "${NAME}")
    set_tests_properties("${NAME}" PROPERTIES DEPENDS "build_${NAME}")

    add_custom_command(
        OUTPUT "clean_${NAME}"
        COMMAND cargo clean
        WORKING_DIRECTORY "${DIR}"
    )
    add_custom_target("clean-${NAME}" DEPENDS "clean_${NAME}")
    add_dependencies("clean-rust" "clean-${NAME}")


endfunction(rust_test)

rust_test(test_object rust_object)
rust_test(test_object_types rust_object_types)
