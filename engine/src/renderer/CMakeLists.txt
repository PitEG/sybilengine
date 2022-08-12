set(RENDERER_SRC
  renderer.cpp
  shader.cpp
  )

set(SRC ${RENDERER_SRC})

add_library(sybilengine_renderer ${SRC})

target_link_libraries(sybilengine_renderer glad SDL2)
target_include_directories(sybilengine_renderer PUBLIC ${SYBIL_ENGINE_INC} .)
