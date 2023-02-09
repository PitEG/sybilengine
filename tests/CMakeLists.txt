find_package(Catch2 REQUIRED)
message("found Catch2")

set(SBL_ECS_TEST
  engine/ecs/test_scene.cpp
  engine/ecs/test_component.cpp
  )

set(SBL_TEST
  ${SBL_ECS_TEST}
  )

add_executable(tests tests.cpp ${SBL_TEST})

# target_link_libraries(tests PRIVATE sybilengine Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE sybilengine Catch2::Catch2)
