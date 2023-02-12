#pragma once

#include "sybilengine/util/freelist.hpp"
#include "sybilengine/audio/channel.hpp"
#include "sybilengine/audio/music.hpp"
#include "sybilengine/audio/sound.hpp"

#include <string>

namespace sbl {
  class Mixer {
  public:
    static const unsigned int DEFAULT_NUM_CHANNELS = 8;
    static FreeList<Channel> Master; 
    static void PlayMusic(const Music& music);
    static void PlaySound(const Sound& sound);
    static void SetMaxChannels(const unsigned int numChannels);
  };
}
