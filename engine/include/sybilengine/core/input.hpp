#pragma once

#include "sybilengine/core/keycode.hpp"

namespace sbl {
  struct Input {
    struct Mouse {
      int x = 0;
      int y = 0;
      bool m1 = false;
      bool m2 = false;
      bool m3 = false;
      bool m4 = false;
      bool m5 = false;
    };
    struct Gamepad {
    };
    const static unsigned int NUM_KEYS = 512;
    const static unsigned int NUM_GAMEPADS = 12;

    Mouse Mouse;
    bool KeyState[NUM_KEYS];
    Gamepad Gamepads[NUM_GAMEPADS];

    inline bool GetKey(KeyCode keycode) const { return KeyState[(int)keycode]; }
  };
}
