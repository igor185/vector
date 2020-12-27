cmake_minimum_required(VERSION 3.15)
project(my_vector
        VERSION 1.0.0
        DESCRIPTION "Add two numbers"
        HOMEPAGE_URL "https://github.com/chernetskyi/cpp-template"
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Options
option(WARNINGS_AS_ERRORS   "Treat compiler warnings as errors."    ON)
option(ENABLE_CONAN         "Use Conan as a package manager."       OFF)
option(ENABLE_PVS_STUDIO    "Use PVS-Studio static code analyzer."  OFF) # Option for the local usage only. PVS-Studio isn't installed on GitHub machines.
option(ENABLE_SANITIZERS    "Use sanitizers to detect errors."      OFF) # Option for the test builds. Do not use it in the production builds.


include_directories(src/vector)

add_executable(main src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


# For testing
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
#find_package(gmock REQUIRED)

add_executable(tests src/vector/tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} Threads::Threads)
enable_testing()
add_test(tests src/vector/tests.cpp)

# Include default CMake configuration
include(cmake/Config.cmake)
