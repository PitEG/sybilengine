#include "sybilengine/audio/mixer.hpp"

#include <SDL2/SDL_mixer.h>

namespace sbl {
  FreeList<Channel> Mixer::Master = FreeList<Channel>(DEFAULT_NUM_CHANNELS);

  void Mixer::Play(const Sound& sound) {
    int result = Mix_PlayChannel(-1, (Mix_Chunk*)sound.data, 0);
  }

  void Mixer::MaxVolume(const float volume) {
    Mix_MasterVolume(60);
  }
}
