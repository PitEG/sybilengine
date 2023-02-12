#include "sybilengine/audio/mixer.hpp"

namespace sbl {
  FreeList<Channel> Mixer::Master = FreeList<Channel>(DEFAULT_NUM_CHANNELS);
}
