add_library(sybilengine SHARED sybilengine.cpp)

add_subdirectory(core)

set(SYBIL_ENGINE_MODULES
  sybilengine_core
  )

target_link_libraries(sybilengine PUBLIC ${SYBIL_ENGINE_MODULES})
target_include_directories(sybilengine PUBLIC ${SYBIL_ENGINE_INC})

# precompiled headers
target_precompile_headers(sybilengine PUBLIC spch.hpp)
