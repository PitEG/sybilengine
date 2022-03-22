# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad)
set(GLAD_INC ${GLAD_DIR}/include)
add_library(glad SHARED ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_INC})
  
# glfw
add_subdirectory(glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# glm
add_subdirectory(glm)

# stb_image
set(STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
set(STB_INC ${STB_DIR})
add_library(stb_image SHARED ${STB_DIR}/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${STB_INC})

# freetype
# add_subdirectory(freetype)

# imgui PASSING THE GLAD IMPLEMENTATION DEFINE, MAYBE MAKE THIS AN OPTION!
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui CACHE PATH "imgui dir in engine vendor")
set(IMGUI_INC ${IMGUI_DIR} ${IMGUI_DIR}/backends CACHE PATH "imgui inc directory")

  # imgui
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
#set_target_properties(imgui_opengl3 PROPERTIES COMPILE_FLAGS "-DIMGUI_IMPL_OPENGL_LOADER_GLAD")
target_compile_definitions(imgui_opengl3 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

  # glfw
add_library(imgui_glfw SHARED ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
target_link_libraries(imgui_glfw glad glfw)
target_include_directories(imgui_glfw PUBLIC ${IMGUI_INC})
#set_target_properties(imgui_glfw PROPERTIES COMPILE_FLAGS "-DIMGUI_IMPL_OPENGL_LOADER_GLAD")
target_compile_definitions(imgui_glfw PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

message("imgui include directories: " ${IMGUI_INC})
# add includes
