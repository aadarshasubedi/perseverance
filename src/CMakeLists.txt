project(perseverance)

set(SOURCE_FILES main.cpp)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

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