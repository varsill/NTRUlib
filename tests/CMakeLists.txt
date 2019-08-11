project(Unit Test Project)
file(GLOB TESTS_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.c)
add_executable(test ${TESTS_SOURCE_FILES})

#dependencies to the main program - NTRU library  
include_directories(${CMAKE_SOURCE_DIR}/include})
target_link_libraries(test ntrulib)

#dependencies required by Check Framework
find_package(Threads REQUIRED)
target_link_libraries(test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test check)
target_link_libraries(test rt)
target_link_libraries(test subunit)


