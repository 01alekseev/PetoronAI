cmake_minimum_required(VERSION 3.20)

project(
    PetoronAIButler
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(
    PETORONAI_BUTLER_BUILD_TESTS
    "Build PetoronAI Butler tests"
    ON
)

set(
    PETORONAI_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
    CACHE PATH
    "PetoronAI root"
)

set(
    PETORONAI_BUILD
    "${PETORONAI_ROOT}/build"
    CACHE PATH
    "PetoronAI build directory"
)

add_library(
    petoron_ai_core
    STATIC
    IMPORTED
)

set_target_properties(
    petoron_ai_core
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONAI_BUILD}/libpetoron_ai.a"
)

add_library(
    zkpetoron_core
    STATIC
    IMPORTED
)

set_target_properties(
    zkpetoron_core
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONAI_BUILD}/zkPetoron-Core/libzkpetoron.a"
)

add_library(
    petoronhash2_core
    STATIC
    IMPORTED
)

set_target_properties(
    petoronhash2_core
    PROPERTIES
        IMPORTED_LOCATION
            "${PETORONAI_BUILD}/zkPetoron-Core/PetoronHash2/libpetoronhash2.a"
)

add_library(
    petoron_ai_butler
    STATIC
    src/petoron_ai_butler.cpp
    src/petoron_ai_butler_agent_cycle.cpp
)

target_include_directories(
    petoron_ai_butler
    PUBLIC
        include
        "${PETORONAI_ROOT}/mind/include"
        "${PETORONAI_ROOT}/zkPetoron-Core"
)

target_link_libraries(
    petoron_ai_butler
    PUBLIC
        petoron_ai_core
        zkpetoron_core
        petoronhash2_core
)

if(PETORONAI_BUTLER_BUILD_TESTS)
    add_executable(
        petoron_ai_butler_test
        tests/petoron_ai_butler_test.cpp
    )

    target_link_libraries(
        petoron_ai_butler_test
        PRIVATE
            petoron_ai_butler
    )

    enable_testing()

    add_test(
        NAME petoron_ai_butler_test
        COMMAND petoron_ai_butler_test
    )
endif()
