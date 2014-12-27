cmake_minimum_required (VERSION 2.8)
project (perseverance)

#Environment variables
set(ENV{SFML_ROOT} "/home/ryan/custom_root")
set(ENV{TMX_LOADER_ROOT} "/home/ryan/custom_root")

#Ensure C++ 11 support
set(CMAKE_CXX_FLAGS "-std=c++11")

#Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
#(you can also set it on the command line: -D CMAKE_BUILD_TYPE=R

set(perseverance_VERSION_MAJOR 1)
set(perseverance_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

#Resource Files
file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

#Source Files
set(SOURCE_FILES src/main.cpp)

configure_file(
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/src/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}/src")

add_executable(perseverance ${SOURCE_FILES})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(perseverance ${SFML_LIBRARIES})
endif()

find_package(TMXLoader REQUIRED)
if (TMX_LOADER_FOUND)
  include_directories(${TMX_LOADER_INCLUDE_PATH})
  target_link_libraries(perseverance ${TMX_LOADER_LIBRARY})
else(TMX_LOADER_FOUND)
  message(FATAL_ERROR "Could not link TMX-loader")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_PATH})
  target_link_libraries(perseverance ${GLEW_LIBRARY})
endif()