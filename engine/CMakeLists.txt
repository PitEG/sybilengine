project(sybilengine)
set(SYBIL_ENGINE_INC ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE FILEPATH "file path to sybilengine include dir")

option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# 3rd party libraries
add_subdirectory(vendor)

# source
add_subdirectory(src)
