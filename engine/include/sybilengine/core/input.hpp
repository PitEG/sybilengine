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
      // these things
      bool start = false;
      bool select = false;
      bool home = false;

      // sticks
      float leftStickX = 0;
      float leftStickY = 0;
      bool leftStickIn = 0;
      float rightStickX = 0;
      float rightStickY = 0;
      bool rightStickIn = 0;

      // dpad
      bool up = false;
      bool down = false;
      bool left = false;
      bool right = false;

      // shoulder buttons
      bool leftBumper = false;
      bool rightBumper = false;
      float leftTrigger = 0;
      float rightTrigger = 0;

      // face buttons
      bool north = false;
      bool south = false;
      bool west = false;
      bool east = false;
    };
    const static unsigned int NUM_KEYS = 512;
    const static unsigned int NUM_GAMEPADS = 12;

    Mouse Mouse;
    bool KeyState[NUM_KEYS];
    Gamepad Gamepads[NUM_GAMEPADS];

    inline bool GetKey(KeyCode keycode) const { return KeyState[(int)keycode]; }
  };
}
