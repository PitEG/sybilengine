# Catch2 C++ testing framework
add_subdirectory(catch2)

set(SBL_ECS_TEST
  engine/ecs/test_transform.cpp
  engine/ecs/test_scene.cpp
  engine/ecs/test_componentmanager.cpp
  engine/ecs/test_component.cpp
  engine/ecs/phys/test_collider.cpp
  engine/ecs/phys/test_collidergrid.cpp
  engine/ecs/phys/test_collision.cpp
  )

set(SBL_UTIL_TEST
  engine/util/test_vector2.cpp
  engine/util/test_circle.cpp
  engine/util/test_bitmask.cpp
  engine/util/test_idmap.cpp
  engine/util/test_freelist.cpp
  )

set(SBL_RENDERER_OPENGL_TEST
# engine/renderer/gl/test_texture.cpp
  )

set(SBL_RENDERER_TEST
  ${SBL_RENDERER_OPENGL_TEST}
  )

set(SBL_TEST
  ${SBL_ECS_TEST}
  ${SBL_UTIL_TEST}
  ${SBL_RENDERER_TEST}
  )

add_executable(tests tests.cpp ${SBL_TEST})

target_link_libraries(tests PRIVATE sybilengine Catch2::Catch2WithMain)

