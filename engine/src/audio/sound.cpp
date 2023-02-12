#include "sybilengine/audio/sound.hpp"

#include <SDL2/SDL_mixer.h>

namespace sbl {
  Sound::Sound(const std::string& file) {
    data = (void*)Mix_LoadWAV(file.c_str());
  }
}
