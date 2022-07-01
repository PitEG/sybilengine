project(sybilsandbox)

# INPUT TESTING
add_executable(inputtest inputpolltest.cpp)
target_link_libraries(inputtest PRIVATE sybilengine)

#[[
# APPLICATION TESTING
add_executable(applicationtest applicationtest.cpp)
target_link_libraries(applicationtest PRIVATE sybilengine)

# OPENGL TESTING
add_executable(opengltest opengltest.cpp)
target_link_libraries(opengltest PRIVATE sybilengine)
configure_file(sybil.png sybil.png COPYONLY)

# PONG
# add_executable(pong pong.cpp)
# target_link_Libraries(pong PRIVATE sybilengine)

# MEMORY TESTING
add_executable(glfwmemtest glfwmemtest.cpp)
target_link_libraries(glfwmemtest PRIVATE glad glfw)
]]

# PHYS STRESS TEST
add_executable(phys_stress phys_stress.cpp)
target_link_Libraries(phys_stress PRIVATE sybilengine)

# IMGUI TEST (DEMO)
add_executable(imgui_test imguitest.cpp)
target_link_Libraries(imgui_test imgui imgui_opengl3 imgui_glfw glad glfw)
target_include_directories(imgui_test PRIVATE ${IMGUI_INC})

