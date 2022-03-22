set(SRC
    logger.cpp
   )

add_library(sybilengine_debug ${SRC})

target_link_libraries(sybilengine_debug)
target_include_directories(sybilengine_debug PUBLIC ${SYBIL_ENGINE_INC})
