set(GLFW_SRC
    glfw/window.cpp
    glfw/input.cpp
   )

set(CORE_SRC
    filesystem.cpp
   )

set(SRC ${GLFW_SRC} ${CORE_SRC})

add_library(sybilengine_core ${SRC})

target_link_libraries(sybilengine_core glad glfw glm)
target_include_directories(sybilengine_core PUBLIC ${SYBIL_ENGINE_INC} .)
