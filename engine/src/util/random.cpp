#include "sybilengine/util/random.hpp"

#include <cstdlib>

namespace sbl {
  Random::Random() 
  : Random(0) {
  }

  Random::Random(int seed) 
  : originalSeed(seed), currentSeed(seed) {

  }

  int Random::RangeInt(const int max) {
    std::srand(currentSeed);
    int random = std::rand();
    currentSeed = random;
    return random % max;
  }

  float Random::RangeFloat(const float max) {
    std::srand(currentSeed);
    int random = std::rand();
    currentSeed = random;
    return random / (RAND_MAX / max);
  }
}