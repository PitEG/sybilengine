set(CORE_SRC
  window.cpp
  )

set(SRC ${CORE_SRC})

add_library(sybilengine_core ${SRC})

target_link_libraries(sybilengine_core PRIVATE SDL2)
target_include_directories(sybilengine_core PUBLIC ${SYBIL_ENGINE_INC} .)
