cmake_minimum_required(VERSION 3.20)

project(
    ButlerHands
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
    BUTLER_HANDS_BUILD_TESTS
    "Build Butler-hands tests"
    ON
)

set(
    PETORONAI_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    CACHE PATH
    "PetoronAI root directory"
)

set(
    PETORONAI_BUILD
    "${PETORONAI_ROOT}/build"
    CACHE PATH
    "PetoronAI build directory"
)

set(
    PETORONAI_BUTLER_ROOT
    "${PETORONAI_ROOT}/PetoronAI-butler"
    CACHE PATH
    "PetoronAI-Butler source directory"
)

set(
    PETORONAI_BUTLER_BUILD
    "${PETORONAI_BUTLER_ROOT}/build"
    CACHE PATH
    "PetoronAI-Butler build directory"
)

set(
    PETORONAI_BUTLER_LIBRARY
    "${PETORONAI_BUTLER_BUILD}/libpetoron_ai_butler.a"
)

set(
    PETORONAI_CORE_LIBRARY
    "${PETORONAI_BUILD}/libpetoron_ai.a"
)

set(
    ZKPETORON_CORE_LIBRARY
    "${PETORONAI_BUILD}/zkPetoron-Core/libzkpetoron.a"
)

set(
    PETORONHASH2_CORE_LIBRARY
    "${PETORONAI_BUILD}/zkPetoron-Core/PetoronHash2/libpetoronhash2.a"
)

foreach(required_path
    "${PETORONAI_BUTLER_ROOT}/include/petoron_ai_butler.hpp"
    "${PETORONAI_BUTLER_LIBRARY}"
    "${PETORONAI_CORE_LIBRARY}"
    "${ZKPETORON_CORE_LIBRARY}"
    "${PETORONHASH2_CORE_LIBRARY}"
)
    if(NOT EXISTS "${required_path}")
        message(
            FATAL_ERROR
            "Required Petoron dependency not found: ${required_path}"
        )
    endif()
endforeach()

add_library(
    petoron_ai_butler
    STATIC
    IMPORTED
    GLOBAL
)

set_target_properties(
    petoron_ai_butler
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONAI_BUTLER_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES
            "${PETORONAI_BUTLER_ROOT}/include;${PETORONAI_ROOT}/mind/include;${PETORONAI_ROOT}/zkPetoron-Core"
)

add_library(
    petoron_ai_core
    STATIC
    IMPORTED
    GLOBAL
)

set_target_properties(
    petoron_ai_core
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONAI_CORE_LIBRARY}"
)

add_library(
    zkpetoron_core
    STATIC
    IMPORTED
    GLOBAL
)

set_target_properties(
    zkpetoron_core
    PROPERTIES
        IMPORTED_LOCATION
            "${ZKPETORON_CORE_LIBRARY}"
)

add_library(
    petoronhash2_core
    STATIC
    IMPORTED
    GLOBAL
)

set_target_properties(
    petoronhash2_core
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONHASH2_CORE_LIBRARY}"
)

add_library(
    butler_hands
    STATIC
    src/runtime.cpp
    src/validation.cpp
    src/file_audit_sink.cpp
)

target_include_directories(
    butler_hands
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(
    butler_hands
    PUBLIC
        cxx_std_20
)

target_link_libraries(
    butler_hands
    PUBLIC
        petoron_ai_butler
        petoron_ai_core
        zkpetoron_core
        petoronhash2_core
)

if(BUTLER_HANDS_BUILD_TESTS)
    enable_testing()

    function(add_butler_hands_test target source)
        add_executable(
            "${target}"
            "${source}"
        )

        target_link_libraries(
            "${target}"
            PRIVATE
                butler_hands
        )

        add_test(
            NAME "${target}"
            COMMAND "${target}"
        )
    endfunction()

    add_butler_hands_test(
        butler_hands_validation_test
        tests/validation_test.cpp
    )

    add_butler_hands_test(
        butler_hands_runtime_e2e_test
        tests/runtime_e2e_test.cpp
    )

    add_butler_hands_test(
        butler_hands_runtime_multicycle_test
        tests/runtime_multicycle_test.cpp
    )

    add_butler_hands_test(
        butler_hands_runtime_failure_stress_test
        tests/runtime_failure_stress_test.cpp
    )

    add_butler_hands_test(
        butler_hands_runtime_deep_test
        tests/runtime_deep_test.cpp
    )

    add_butler_hands_test(
        butler_hands_runtime_timeout_test
        tests/runtime_timeout_test.cpp
    )
endif()
