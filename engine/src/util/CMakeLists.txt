set(SRC
  math.cpp
  random.cpp
  time.cpp
  stopwatch.cpp
  )

add_library(sybilengine_util ${SRC})

target_include_directories(sybilengine_util PUBLIC ${SYBIL_ENGINE_INC} .)
