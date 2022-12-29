# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad)
set(GLAD_INC ${GLAD_DIR}/include)
add_library(glad SHARED ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_INC})

# GLM
find_package(glm REQUIRED)
message("found glm")
include_directories(${GLM_INCLUDE_DIRS})
message("added glm")

# SDL2
find_package(SDL2 REQUIRED)
message("found SDL2")
include_directories(${SDL2_INCLUDE_DIRS})
message("added SDL2")

# STB IMAGE
set(STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stbimage)
set(STB_INC ${STB_DIR})
add_library(stb_image SHARED ${STB_DIR}/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${STB_INC})

# IMGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui CACHE PATH "imgui dir in engine vendor")
set(IMGUI_INC ${IMGUI_DIR} ${IMGUI_DIR}/backends CACHE PATH "imgui inc directory")

add_library(imgui SHARED 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp) # this last one is optional really. Only need it for the demo

  # opengl3 
add_library(imgui_opengl3 SHARED ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
target_link_libraries(imgui_opengl3 glad)
target_include_directories(imgui_opengl3 PUBLIC ${IMGUI_INC})
target_compile_definitions(imgui_opengl3 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

  # sdl2 
add_library(imgui_sdl2 SHARED ${IMGUI_DIR}/backends/imgui_impl_sdl.cpp)
target_link_libraries(imgui_sdl2 glad SDL2)
target_include_directories(imgui_sdl2 PUBLIC ${IMGUI_INC})
target_compile_definitions(imgui_sdl2 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
