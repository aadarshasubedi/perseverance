cmake_minimum_required (VERSION 2.6)
project (perseverance)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=R

set(perseverance_VERSION_MAJOR 1)
set(perseverance_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

set(ENV{SFML_ROOT} "/home/ryan/custom_root")

add_subdirectory (src)