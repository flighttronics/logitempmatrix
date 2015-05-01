cmake_minimum_required(VERSION 2.8)

# Project defines
project(LOGITEMPMATRIX)
SET(VESRION_MAJOR "0")
SET(VESRION_MINOR "1")
SET(VESRION_PATCH "0")
SET(VERSION "$(VESRION_MAJOR).$(VESRION_MINOR).$(VESRION_PATCH)")

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
  ADD_DEFINITIONS(-g -O2 -Wall -W -Wextra )
    #SET(CMAKE_CXX_FLAGS "-g -O2 -Wall")   ## Optimize
    #SET(CMAKE_EXE_LINKER_FLAGS "-s -lm")  ## Strip binary
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Make sure the compiler can find include files 
#include_directories (${ALM3AUDIO_SOURCE_DIR}/lib/gpsd)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
SET(LIBRGBMATRIX_DIR "rpi-rgb-led-matrix")
SET(LIBRGBMATRIX_LIB_DIR ${PROJECT_SOURCE_DIR}/${LIBRGBMATRIX_DIR}/lib)
SET(LIBCURLCPP_DIR "curlcpp")
SET(LIBCURLCPP_LIB_DIR ${PROJECT_SOURCE_DIR}/${LIBCURLCPP_DIR}/build/src)

#Include directories
include_directories("rpi-rgb-led-matrix/include")
include_directories("${PROJECT_SOURCE_DIR}/rpi-rgb-led-matrix")

#Subdirectory
add_subdirectory("src")

# Messages
MESSAGE( STATUS "CMAKE_BINARY_DIR:          " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "INSTALL_CMAKE_DIR:         " ${INSTALL_CMAKE_DIR} )
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH:    " ${EXECUTABLE_OUTPUT_PATH} )
MESSAGE( STATUS "PROJECT_BINARY_DIR:        " ${PROJECT_BINARY_DIR} )
MESSAGE( STATUS "PROJECT_SOURCE_DIR:        " ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "LOGITEMPMATRIX_SOURCE_DIR: " ${LOGITEMPMATRIX_SOURCE_DIR})
