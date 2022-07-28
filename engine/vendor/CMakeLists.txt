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
