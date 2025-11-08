cmake_minimum_required(VERSION 3.10)

project(lab4 
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

add_executable(lab4_main main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab4_tests ${TEST_DIR}/test.cpp)
target_link_libraries(lab4_tests PRIVATE gtest_main)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab4_main PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab4_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(lab4_tests)