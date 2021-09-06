get_filename_component(RELATIVE_CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("Running CMAKE in directory: " ${RELATIVE_CURRENT_DIRECTORY})

cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME _SyndromeDecodingEstimator)
SET(EXECUTABLE_NAME ${PROJECT_NAME}-bin)
set(MINIMUM_VERSION VERSION 3.7)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# GENERATE testall.c FILE
# -----------------------

# TODO

# -----------------------

enable_testing()

message(STATUS "BUILDING IN ${CMAKE_BUILD_TYPE} MODE")
message(STATUS "COMPILATION FLAGS: ${CMAKE_C_FLAGS}")

# INCLUDE SUBDIRECTORIES
# ----------------------

set(SRC_DIRECTORY_NAME src)
set(TESTS_DIRECTORY_NAME tests)
set(BENCHMARKS_DIRECTORY_NAME benchmarks)
set(EXAMPLES_DIRECTORY_NAME examples)
set(MAIN_DIRECTORY_NAME main)

file(GLOB SRC_DIRECTORY_LIST ${SRC_DIRECTORY_NAME}/* )
file(GLOB TESTS_DIRECTORY_LIST  ${TESTS_DIRECTORY_NAME}/*)
file(GLOB BENCHMARKS_DIRECTORY_LIST  ${BENCHMARKS_DIRECTORY_NAME}/*)
file(GLOB EXAMPLES_DIRECTORY_LIST  ${EXAMPLES_DIRECTORY_NAME}/*)
#file(GLOB MAIN_DIRECTORY_LIST ${MAIN_DIRECTORY_NAME}/*)

message( STATUS "Adding the following directories to the project: ")

FOREACH(DIR ${SRC_DIRECTORY_LIST})
    message(STATUS "Adding directory: " ${DIR})
    add_subdirectory(${DIR})
ENDFOREACH()

FOREACH(DIR ${TESTS_DIRECTORY_LIST})
    add_subdirectory(${DIR})
ENDFOREACH()

FOREACH(DIR ${BENCHMARKS_DIRECTORY_LIST})
    add_subdirectory(${DIR})
ENDFOREACH()

FOREACH(DIR ${EXAMPLES_DIRECTORY_LIST})
    add_subdirectory(${DIR})
ENDFOREACH()

add_subdirectory(${MAIN_DIRECTORY_NAME})
#FOREACH(DIR ${MAIN_DIRECTORY_LIST})
#    add_subdirectory(${DIR})
#ENDFOREACH()

message("Back to main cmake:")

# ADD TARGET TO LIBRARY
# ---------------------

message( STATUS "Adding the following targets to the project: ")

# NOTE: make sure that no header .h file are present in the line below, otherwise it will cause duplicated symbol error during linking
set(TARGET_LIST "" src/sd_estimator/sd_estimator.cpp src/sd_estimator/sd_helper.cpp src/sd_estimator/sd_both_may_depth_2.cpp src/sd_estimator/sd_optimizer.cpp src/sd_estimator/sd_ball_collision_optimizer.cpp src/sd_estimator/sd_bjmm_optimizer.cpp src/sd_estimator/sd_dumer_optimizer.cpp src/sd_estimator/sd_may_ozerov_optimizer.cpp src/sd_estimator/sd_stern_optimizer.cpp)
set(TARGET_LIST_LIB "" ${TARGET_LIST})
list(APPEND TARGET_LIST "" main/main.cpp)

FOREACH(DIR ${SRC_DIRECTORY_LIST})
    get_filename_component(RELATIVE_DIR ${DIR} NAME)
    message("    " ${RELATIVE_DIR} )
    list(APPEND TARGET_LIST "$<TARGET_OBJECTS:${RELATIVE_DIR}>")
ENDFOREACH()

message("Targets list:" ${TARGET_LIST})
add_library(${PROJECT_NAME} SHARED ${TARGET_LIST_LIB})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "usr/local/lib")

#install(FILES DESTINATION include)



