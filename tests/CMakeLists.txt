cmake_minimum_required(VERSION 2.6)
project(UnitTestProject)
file(GLOB TESTS_SOURCE_FILES )
add_executable(polynomial_test ${PROJECT_SOURCE_DIR}/src/polynomial_test.c)
add_executable(rationals_test ${PROJECT_SOURCE_DIR}/src/rationals_test.c)
add_executable(ntru_test ${PROJECT_SOURCE_DIR}/src/ntru_test.c)
#dependencies to the main program - NTRU library  
include_directories(${CMAKE_SOURCE_DIR}/include})
target_link_libraries(polynomial_test ntrulib)

target_link_libraries(rationals_test ntrulib)

target_link_libraries(ntru_test ntrulib)

#dependencies required by Check Framework
find_package(Threads REQUIRED)
target_link_libraries(polynomial_test ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(polynomial_test check)
target_link_libraries(polynomial_test rt)
target_link_libraries(polynomial_test subunit)
target_link_libraries(polynomial_test pthread)
target_link_libraries(polynomial_test m)

target_link_libraries(rationals_test ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(rationals_test check)
target_link_libraries(rationals_test rt)
target_link_libraries(rationals_test subunit)
target_link_libraries(rationals_test pthread)
target_link_libraries(rationals_test m)


target_link_libraries(ntru_test ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ntru_test check)
target_link_libraries(ntru_test rt)
target_link_libraries(ntru_test subunit)
target_link_libraries(ntru_test pthread)
target_link_libraries(ntru_test m)



