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
    static FreeList<Channel> Master; // not needed... right now
    static void Play(const Music& music);
    static void Play(const Sound& sound);
    static void SetMaxChannels(const unsigned int numChannels);
    static void MaxVolume(const float volume);
  };
}
