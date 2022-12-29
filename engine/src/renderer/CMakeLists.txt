set(RENDERER_SRC
  renderer.cpp
  shader.cpp
  texture.cpp
  framebuffer.cpp
  )

set(SRC ${RENDERER_SRC})

add_library(sybilengine_renderer ${SRC})

target_link_libraries(sybilengine_renderer glad SDL2 stb_image)
target_include_directories(sybilengine_renderer PUBLIC ${SYBIL_ENGINE_INC} .)
