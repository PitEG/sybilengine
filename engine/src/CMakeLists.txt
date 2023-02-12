add_library(sybilengine SHARED sybilengine.cpp)

add_subdirectory(core)
add_subdirectory(util)
add_subdirectory(renderer)
add_subdirectory(ecs)
add_subdirectory(audio)

set(SYBIL_ENGINE_MODULES
  sybilengine_core
  sybilengine_util
  sybilengine_renderer
  sybilengine_ecs
  sybilengine_audio
  )

target_link_libraries(sybilengine PUBLIC ${SYBIL_ENGINE_MODULES} SDL2_mixer)
target_include_directories(sybilengine PUBLIC ${SYBIL_ENGINE_INC})

# precompiled headers
target_precompile_headers(sybilengine PUBLIC spch.hpp)
