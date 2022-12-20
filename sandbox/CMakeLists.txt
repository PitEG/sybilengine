project(sybilsandbox)

# core processes 
add_executable(core core.cpp)
target_link_libraries(core PRIVATE sybilengine)

# renderer testing
add_executable(renderer renderer.cpp)
target_link_libraries(renderer PRIVATE sybilengine SDL2)

# batch renderer testing
add_executable(batch_renderer batch_renderer.cpp)
target_link_libraries(batch_renderer PRIVATE sybilengine SDL2)

# imgui test
add_executable(imgui_test imgui_test.cpp)
target_link_libraries(imgui_test PRIVATE imgui imgui_sdl2 imgui_opengl3 glad SDL2)
