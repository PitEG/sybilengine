set(CORE_SRC
  window.cpp
  imgui.cpp
  )

set(SRC ${CORE_SRC})

add_library(sybilengine_core ${SRC})

target_link_libraries(sybilengine_core glad SDL2 imgui imgui_sdl2 imgui_opengl3)
target_include_directories(sybilengine_core PUBLIC ${SYBIL_ENGINE_INC} .)
