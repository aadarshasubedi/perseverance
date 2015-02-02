cmake_minimum_required (VERSION 2.8)
project (perseverance)

#Environment variables
set(ENV{SFML_ROOT} "/home/ryan/custom_root")
set(ENV{TMX_LOADER_ROOT} "/home/ryan/custom_root")
set(ENV{SFGUI_ROOT} "/home/ryan/custom_root")

#Ensure C++ 11 support
set(CMAKE_CXX_FLAGS "-std=c++11")

#Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(perseverance_VERSION_MAJOR 1)
set(perseverance_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

#Source Files
set(SOURCE_FILES src/main.cpp
                 src/Application.cpp
                 src/Hero.cpp
                 src/World.cpp
                 src/Player.cpp
                 src/state/State.cpp
                 src/state/GameState.cpp
                 src/state/StateStack.cpp
                 src/state/TitleState.cpp
                 src/state/PauseState.cpp
                 src/state/MainMenuState.cpp
                 src/state/LoadingState.cpp
                 src/util/Command.cpp
                 src/util/CommandQueue.cpp
                 src/util/SceneNode.cpp
                 src/util/Entity.cpp
                 src/util/Utility.cpp
                 src/state/ResourceLoaderTask.cpp
                 src/util/ext/Animation.cpp
                 src/util/ext/AnimatedSprite.cpp)

#Headers
configure_file(
  "include/config/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}/include")
include_directories(include)

#Executable Target
add_executable(perseverance ${SOURCE_FILES})

#SFML 2.0
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(perseverance ${SFML_LIBRARIES})
endif()

#SFML 2.0 TMX (Tiled) Map loader
find_package(TMXLoader REQUIRED)
if (TMX_LOADER_FOUND)
  include_directories(${TMX_LOADER_INCLUDE_PATH})
  target_link_libraries(perseverance ${TMX_LOADER_LIBRARY})
else(TMX_LOADER_FOUND)
  message(FATAL_ERROR "Could not link TMX-loader")
endif()

#GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_PATH})
  target_link_libraries(perseverance ${GLEW_LIBRARY})
endif()

#SFGUI
find_package( SFGUI REQUIRED )
if (SFGUI_FOUND)
 include_directories( ${SFGUI_INCLUDE_DIR} )
 target_link_libraries( perseverance ${SFGUI_LIBRARY})
endif()

#Ensure latest resources are always copied
add_custom_target(resources_copy)
get_target_property(perseverance_location perseverance LOCATION)
get_filename_component(perseverance_dir ${perseverance_location} PATH)
add_custom_command(TARGET resources_copy PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy_directory ${CMAKE_SOURCE_DIR}/resources ${perseverance_dir}/resources)
add_dependencies(perseverance resources_copy)