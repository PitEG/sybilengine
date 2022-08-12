add_library(sybilengine SHARED sybilengine.cpp)

add_subdirectory(core)
add_subdirectory(util)
add_subdirectory(renderer)

set(SYBIL_ENGINE_MODULES
  sybilengine_core
  sybilengine_util
  sybilengine_renderer
  )

target_link_libraries(sybilengine PUBLIC ${SYBIL_ENGINE_MODULES})
target_include_directories(sybilengine PUBLIC ${SYBIL_ENGINE_INC})

# precompiled headers
target_precompile_headers(sybilengine PUBLIC spch.hpp)
