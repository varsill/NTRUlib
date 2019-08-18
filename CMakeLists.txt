#Set general options
	cmake_minimum_required(VERSION 2.6)
	project(NTRULibrary)

#Configure
	option(TEST "ON when the project is about to be tested using unit tests" ON)
	set(VERSION_MAJOR 1)
	set(VERSION_MINOR 0)
	configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

#Add headers and source files
	include_directories(${PROJECT_SOURCE_DIR}/include)
	file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

#Create library
	add_library(ntrulib ${SRC_FILES}  ${PROJECT_SOURCE_DIR}/src/quotient_polynominal_ring.c)

#Add additional dependencies:
	#set(LIBS ${LIBS} library)
	#set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} path_to_file_with_headers)
	include_directories(${ADDITIONAL_INCLUDES})
	#target_link_libraries(ntrulib ${LIBS})

if(TEST)
add_subdirectory(tests)
endif()


