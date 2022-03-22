# SYBIL ENGINE 
add_library(sybilengine SHARED sybilengine.cpp application.cpp)

# CORE
add_subdirectory(core)
# UTIL
add_subdirectory(util)
# DEBUG 
add_subdirectory(debug)
# IMGUI 
add_subdirectory(imgui)
# ECS 
add_subdirectory(ecs)
# RENDERER
add_subdirectory(renderer)

set(SYBIL_ENGINE_MODULES 
    sybilengine_core
    sybilengine_util
    sybilengine_imgui
    sybilengine_debug
    sybilengine_renderer
    sybilengine_ecs
   )

# LINKING SYBIL ENGINE
target_link_libraries(sybilengine PUBLIC ${SYBIL_ENGINE_MODULES})
target_include_directories(sybilengine PUBLIC ${SYBIL_ENGINE_INC})

# PRECOMPILED HEADERS 
target_precompile_headers(sybilengine PUBLIC spch.hpp)
