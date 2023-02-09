set(ECS_SRC
  entity.cpp
  scene.cpp
  )

set(SRC ${ECS_SRC})

add_library(sybilengine_ecs ${SRC})

target_include_directories(sybilengine_ecs PUBLIC ${SYBIL_ENGINE_INC} .)
