set(SRC
    scene.cpp
    phys/collider.cpp
    phys/collidergrid.cpp
    phys/collision.cpp
    phys/collisionmatrix.cpp
  )

add_library(sybilengine_ecs ${SRC})

target_link_libraries(sybilengine_ecs glm)
target_include_directories(sybilengine_ecs PUBLIC ${SYBIL_ENGINE_INC})

