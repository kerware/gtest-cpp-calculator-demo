cmake_minimum_required(VERSION 3.20)

project(gtest_cpp_calculator_demo
    VERSION 1.0.0
    DESCRIPTION "Projet C++17 CMake illustrant GoogleTest du niveau débutant au niveau expert"
    LANGUAGES CXX
)

option(ENABLE_COVERAGE "Enable coverage flags for GCC/Clang" OFF)
option(USE_SYSTEM_GTEST "Use a system-installed GoogleTest package instead of FetchContent" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(ENABLE_COVERAGE AND NOT MSVC)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_library(calculator_lib
    src/calculator.cpp
    src/expression_evaluator.cpp
    src/history_repository.cpp
    src/operation_service.cpp
)

target_include_directories(calculator_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(calculator_cli
    src/main.cpp
)

target_link_libraries(calculator_cli PRIVATE calculator_lib)

enable_testing()

if(USE_SYSTEM_GTEST)
    find_package(GTest REQUIRED)
else()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # Recommandé sous Windows pour éviter les conflits de runtime MSVC.
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(calculator_tests
    tests/01_beginner_assertions_test.cpp
    tests/02_simple_fixture_test.cpp
    tests/03_parameterized_test.cpp
    tests/04_combinatorial_test.cpp
    tests/05_exception_and_post_mortem_test.cpp
    tests/06_complex_fixture_test.cpp
    tests/07_typed_test.cpp
    tests/08_gmock_collaboration_test.cpp
    tests/09_custom_listener_and_metadata_test.cpp
)

target_link_libraries(calculator_tests
    PRIVATE
        calculator_lib
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests
    DISCOVERY_TIMEOUT 30
    PROPERTIES LABELS "unit;gtest"
)
