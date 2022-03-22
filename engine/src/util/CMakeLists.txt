set(SRC
    time.cpp
    stopwatch.cpp
    vector2.cpp
    rect.cpp
    circle.cpp
    line.cpp
    bitmask.cpp
    random.cpp
    math.cpp
    )

add_library(sybilengine_util ${SRC})

target_link_libraries(sybilengine_util glfw glm)
target_include_directories(sybilengine_util PUBLIC ${SYBIL_ENGINE_INC})
