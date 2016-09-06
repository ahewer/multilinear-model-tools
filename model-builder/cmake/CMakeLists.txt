cmake_minimum_required(VERSION 2.7)
PROJECT(model-builder)

SET(CMAKE_BUILD_TYPE release)
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -std=c++11 -march=native -Wall -Wextra -pedantic")
SET(CMAKE_C_FLAGS_RELEASE "-O2 -std=c++11 -march=native -Wall -Wextra -pedantic")
INCLUDE(ConfigureARMADILLO.cmake)
INCLUDE(ConfigureYAMLCPP.cmake)

IF(ARMADILLO_FOUND AND YAMLCPP_FOUND)
  SET(SRC_FILE "../src/bin/main.cpp")

  INCLUDE_DIRECTORIES("../../shared")
  INCLUDE_DIRECTORIES("../src/include")
  INCLUDE_DIRECTORIES(${ARMADILLO_INCLUDE_DIR})
  INCLUDE_DIRECTORIES(${YAMLCPP_INCLUDE_DIR})

  ADD_EXECUTABLE(model-builder ${SRC_FILE})
  TARGET_LINK_LIBRARIES(model-builder
    ${ARMADILLO_LIBRARIES}
    ${YAMLCPP_LIBRARIES}
    )

ELSE(ARMADILLO_FOUND AND YAMLCPP_FOUND)
  Message("PROBLEM: One of the required libraries not found. model-builder will not be compiled.")
ENDIF(ARMADILLO_FOUND AND YAMLCPP_FOUND)
