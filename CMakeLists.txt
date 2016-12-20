cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

project(csvxx
        VERSION 0.1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

include_directories(${INC_DIR})

find_package(GTest)
if(GTEST_FOUND)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    enable_testing()

    add_executable(GTestMain
                   ${TEST_DIR}/field_test.cpp)

    target_include_directories(GTestMain SYSTEM
                               PRIVATE ${GTEST_INCLUDE_DIR})
    target_link_libraries(GTestMain ${GTEST_BOTH_LIBRARIES} Threads::Threads)

    add_test(NAME UnitTests COMMAND GTestMain)
endif()

