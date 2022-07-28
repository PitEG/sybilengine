project(sybilsandbox)

# core processes 
add_executable(core core.cpp)
target_link_libraries(core PRIVATE sybilengine)

# imgui test
add_executable(imgui_test imgui_test.cpp)
target_link_libraries(imgui_test PRIVATE imgui imgui_sdl2 imgui_opengl3 glad SDL2)
