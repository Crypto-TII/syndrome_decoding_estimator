get_filename_component(RELATIVE_CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("Running CMAKE in directory: " ${RELATIVE_CURRENT_DIRECTORY})

cmake_minimum_required(VERSION 3.7)
project(${PROJECT_NAME})

# ADD .c AND .h FILES
# -------------------

file(GLOB SOURCE_LIST *.cpp)
message( STATUS "Adding the following .cpp files to the source list: ")
FOREACH(FILE ${SOURCE_LIST})
    message("    " ${FILE} )
ENDFOREACH()

file(GLOB HEADER_LIST *.h)
message( STATUS "Adding the following .h files to the header list: ")
FOREACH(FILE ${HEADER_LIST})
    message("    " ${FILE} )
ENDFOREACH()


set(SRC ${SOURCE_LIST})
set(HDR ${HEADER_LIST})

# INCLULDE DIRECTORIES
# --------------------

file(GLOB TESTS_DIRECTORY_LIST ${CMAKE_SOURCE_DIR}/tests/* )
file(GLOB BENCHMARKS_DIRECTORY_LIST ${CMAKE_SOURCE_DIR}/benchmarks/* )
file(GLOB EXAMPLES_DIRECTORY_LIST ${CMAKE_SOURCE_DIR}/examples/* )

message( STATUS "Including the following directories: ")
FOREACH(DIR ${TESTS_DIRECTORY_LIST})
    message("    " ${DIR} )
ENDFOREACH()
FOREACH(DIR ${BENCHMARKS_DIRECTORY_LIST})
    message("    " ${DIR} )
ENDFOREACH()
FOREACH(DIR ${EXAMPLES_DIRECTORY_LIST})
    message("    " ${DIR} )
ENDFOREACH()
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${TESTS_DIRECTORY_LIST})
include_directories(${BENCHMARKS_DIRECTORY_LIST})
include_directories(${EXAMPLES_DIRECTORY_LIST})

# ADD EXECUTABLE
# --------------

#set(EXECUTABLE_NAME ${EXECUTABLE_NAME})

#add_executable(${EXECUTABLE_NAME} ${SRC})
#add_dependencies(${EXECUTABLE_NAME} ${PROJECT_NAME})

# LINK TARGET TO LIBRARY
# ----------------------

message( STATUS "Linking the following targets to the project1: ")
set(TARGET_LIBRARY_LIST "")
FOREACH(DIR ${TESTS_DIRECTORY_LIST})
    get_filename_component(RELATIVE_DIR ${DIR} NAME)
    IF (NOT ${RELATIVE_DIR} MATCHES "testall")
        message("    " test_${RELATIVE_DIR} )
        list(APPEND TARGET_LIBRARY_LIST "test_${RELATIVE_DIR}")
    ENDIF ()
ENDFOREACH()

FOREACH(DIR ${BENCHMARKS_DIRECTORY_LIST})
    get_filename_component(RELATIVE_DIR ${DIR} NAME)
    message("    " benchmark_${RELATIVE_DIR} )
    list(APPEND TARGET_LIBRARY_LIST "benchmark_${RELATIVE_DIR}")
ENDFOREACH()

FOREACH(DIR ${EXAMPLES_DIRECTORY_LIST})
    get_filename_component(RELATIVE_DIR ${DIR} NAME)
    message("    " example_${RELATIVE_DIR} )
    list(APPEND TARGET_LIBRARY_LIST "example_${RELATIVE_DIR}")
ENDFOREACH()

#target_link_libraries(${EXECUTABLE_NAME} ${TARGET_LIBRARY_LIST} ${PROJECT_NAME})

#install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/kat DESTINATION bin)