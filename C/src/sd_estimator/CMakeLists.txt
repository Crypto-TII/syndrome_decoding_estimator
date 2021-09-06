get_filename_component(RELATIVE_CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("Running CMAKE in directory: " ${RELATIVE_CURRENT_DIRECTORY})

cmake_minimum_required(VERSION 3.7)
project(${PROJECT_NAME})

# ADD .c AND .h FILES
# -------------------

file(GLOB SOURCE_LIST *.cpp)
message( STATUS "Adding the following .c files to the source list: ")
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


# INCLUDE DIRECTORIES
# -------------------

include_directories(${CMAKE_SOURCE_DIR})

# SET ERRORS
# ----------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

# ADD LIBRARY AND INSTALL
# -----------------------

add_library(${RELATIVE_CURRENT_DIRECTORY} OBJECT ${SRC})

#install(FILES ${HDR} DESTINATION include/${RELATIVE_CURRENT_DIRECTORY})