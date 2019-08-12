cmake_minimum_required(VERSION 2.6)
project(UnitTestProject)
file(GLOB TESTS_SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(unit_test ${TESTS_SOURCE_FILES})

#dependencies to the main program - NTRU library  
include_directories(${CMAKE_SOURCE_DIR}/include})
target_link_libraries(unit_test ntrulib)

#dependencies required by Check Framework
find_package(Threads REQUIRED)
target_link_libraries(unit_test ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unit_test check)
target_link_libraries(unit_test rt)
target_link_libraries(unit_test subunit)
target_link_libraries(unit_test pthread)
target_link_libraries(unit_test m)
