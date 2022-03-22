set(SRC
    imgui.cpp)

add_library(sybilengine_imgui ${SRC})
target_link_libraries(sybilengine_imgui 
    glad glm glfw imgui imgui_opengl3 imgui_glfw)
target_include_directories(sybilengine_imgui PUBLIC ${IMGUI_INC} ${SYBIL_ENGINE_INC})
