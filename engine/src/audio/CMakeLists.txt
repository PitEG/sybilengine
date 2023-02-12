set(AUDIO_SRC
  mixer.cpp
  sound.cpp
  )

set(SRC ${AUDIO_SRC})

add_library(sybilengine_audio ${SRC})

target_link_libraries(sybilengine_audio SDL2_mixer)
target_include_directories(sybilengine_audio PUBLIC ${SYBIL_ENGINE_INC} .)
