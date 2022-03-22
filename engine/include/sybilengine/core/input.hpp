/*
 * not sure how to go about this
 */
#pragma once  

#include "sybilengine/core/keycode.hpp"

namespace sbl {
  /**
   * @brief Stores states of peripheral devices. Used in tandem with the Window
   * class to poll inputs whenever you want.
   * 
   */
  class Input {
  public:
    /*
     * INPUT STRUCTS
     */

    /**
     * @brief Mouse struct representing different states of Mouse input
     */
    struct Mouse {
      /* Cursor Position by pixel from the top left of window */

      /** 
       *  @brief X position on the window. 
       */
      double xPos = 0;

      /** 
       *  @brief Y position on the window. 
       */
      double yPos = 0;

      /** 
       * @brief Primary Click (usually physically Left Click) 
       */
      bool m1 = false; 

      /** 
       * @brief Secondary Click (usually physically Right Click) 
       */
      bool m2 = false; 

      /** 
       * @brief Middle Mouse Click 
       */
      bool m3 = false;

      /** 
       * @brief Thumb Button 1 Click 
       */
      bool m4 = false;

      /** 
       * @brief Thumb Button 2 Click 
       */
      bool m5 = false;
    };

    /**
     * @brief Window Size Event. Sizes measured in pixels.
     */
    struct WindowSize {
      /**
       * @brief Width of the Window.
       */
      unsigned int width  = 1;
      /**
       * @brief Height of the Window.
       */
      unsigned int height = 1;
    };

    /**
     * @brief Gamepad Input States.
     */
    struct Gamepad { 
      /** 
       * @brief stick struct. I don't want to use a Vector2 class to reduce dependencies
       */
      struct Stick {
        /** 
         * @brief X position ranging from [0,1]
         */
        float x = 0.0f;
        /** 
         * @brief Y position ranging from [0,1]
         */
        float y = 0.0f;
      }; 

      /** 
       * @brief If it's active 
       */
      bool active = false;

      //sticks
      /** 
       * @brief Left Stick 
       */
      Stick leftStick;  
      /** 
       * @brief Right Stick 
       */
      Stick rightStick;
      /** 
       * @brief Left Stick Button
       */
      bool leftStickIn  = false;
      /** 
       * @brief Right Stick Button
       */
      bool rightStickIn = false;

      //dpad
      /** 
       * @brief DPAD Up 
       */
      bool up     = false;
      /** 
       * @brief DPAD Down
       */
      bool down   = false;
      /** 
       * @brief DPAD Left 
       */
      bool left   = false;
      /** 
       * @brief DPAD Right 
       */
      bool right  = false;

      //face buttons
      /** 
       * @brief North Button (XBOX: Y, PlayStation: Triangle) 
       */ 
      bool north  = false;
      /** 
       * @brief South Button (XBOX: A, PlayStation: X/Cross) 
       */
      bool south  = false;
      /** 
       * @brief West Button (XBOX: X, PlayStation: Square) 
       */
      bool west   = false;
      /** 
       * @brief East Button (XBOX: B, PlayStation: Circle) 
       */
      bool east   = false;

      //bumpers/triggers
      /** 
       * @brief Left Bumper Digital Input 
       */
      bool leftBumper    = false;
      /** 
       * @brief Right Bumper Digital Input 
       */ 
      bool rightBumper   = false;
      /** 
       * @brief Left Bumper Analog Input. Range from [0,1] 
       */
      float leftTrigger  = 0.0f;
      /** 
       * @brief Right Bumper Analog Input. Range from [0,1] 
       */
      float rightTrigger = 0.0f;

      //function buttons
      /** 
       * @brief Start Button 
       */
      bool start  = false; 
      /** 
       * @brief Select Button 
       */
      bool select = false; 
      /** 
       * @brief Home Button 
       */
      bool home   = false; 
    }; //END GAMEPAD

  public:
    /*
     * CONSTRUCTOR 
     */
    //Input(); //probably no need to implement

    /*
     * STATIC MEMBERS
     */

    /** 
     * @brief Total Number of Gamepads. GLFW supports up to 16. 
     */
    static constexpr int NUM_GAMEPADS = 16; 
    /** 
     * @brief Total Number of keyboard keys. GLFW uses up to about 400 ids. 
     */
    static constexpr int NUM_KEYS = 512; 

    /*
     * MEMBERS
     */

    /** 
     * @brief An array of bools representing the current digital states of Keyboard keys. 
     */
    bool        KeyC[NUM_KEYS]; 
    /** 
     * @brief Mouse state 
     */
    Mouse       Mouse; 
    /** 
     * @brief Gamepad States. There are NUM_GAMEPADS at most 
     */
    Gamepad     Gamepads[NUM_GAMEPADS]; 
    /** 
     * @brief Window size state 
     */
    WindowSize  WindowSize; 

    /*
     * METHODS
     */

    /**
     * @brief Get the Key object. It access the stored bools in this object.
     * 
     * @param keycode KeyCode to check.
     * @return true If the Key is not pressed in this object.
     * @return false If the Key is not pressed in this object.
     */
    inline bool GetKey(KeyCode keycode) const { return KeyC[(int)keycode]; }

  }; //end input
} //end sbl
