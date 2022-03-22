set(OPENGL_SRC
    opengl/bufferlayout.cpp           
    opengl/elementbuffer.cpp           
    opengl/framebuffer.cpp           
    opengl/shader.cpp           
    opengl/vertexarray.cpp           
    opengl/vertexbuffer.cpp           
    opengl/texture.cpp           
    opengl/viewport.cpp
    opengl/bufferbits.cpp  
    opengl/blendmode.cpp  
   )

set(RENDERER_SRC
    rectangleshape.cpp
    lineshape.cpp
    texture.cpp
    renderwindow.cpp
    view.cpp
    sprite.cpp
    spriteatlas.cpp
    renderer.cpp
    renderbatch.cpp
   )

set(SRC
    ${OPENGL_SRC}
    ${RENDERER_SRC}
   )

add_library(sybilengine_renderer ${SRC})

target_link_libraries(sybilengine_renderer glfw glad glm stb_image)
target_include_directories(sybilengine_renderer PUBLIC ${SYBIL_ENGINE_INC})
