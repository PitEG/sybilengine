/*
 * CURRENTLY IMPLEMENT GLAD AND GLFW. IDK IF THIS IS MESSY :(
 */
#include <GLFW/glfw3.h>

#include <cmath>

#include "sybilengine/core/window.hpp"
#include "gamepadmappings.hpp"

namespace sbl { 
  /*
   * CONSTRUCTOR
   */
  Window::Window(
      const std::string name, 
      const unsigned int w, const unsigned int h, 
      const bool resizable)
  : m_name(name), m_width(w), m_height(h) {
    //set hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    if (resizable) {
      glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }
    else {
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
    //TODO write a macro for this or something
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create GLFW window 
    m_window = (void*)glfwCreateWindow(w, h, name.c_str(), NULL, NULL); 

  }

  Window::~Window() {
    glfwDestroyWindow((GLFWwindow*)m_window); 
  }

  /*
   * GETTERS
   */ 
  bool Window::ShouldClose() {
    if (glfwWindowShouldClose((GLFWwindow*)m_window)) {
      m_shouldClose = true;
    }
    if (m_shouldClose) {
      glfwSetWindowShouldClose((GLFWwindow*)m_window, true);
    }

    return m_shouldClose;
  }

  bool Window::IsOpen() {
    if (glfwWindowShouldClose((GLFWwindow*)m_window)) {
      m_shouldClose = true;
    }
    if (m_shouldClose) {
      glfwSetWindowShouldClose((GLFWwindow*)m_window, true);
    }

    return !m_shouldClose;
  }

  void Window::RefreshSize() {
    int w, h;
    glfwGetWindowSize((GLFWwindow*)m_window, &w, &h);
    m_width = w;
    m_height = h;
  }

  /*
   * SETTERS
   */
  //VSYNC
  void Window::SetVsync(bool enabled) {
    if (enabled) {
      glfwSwapInterval(1);
    }
    else {
      glfwSwapInterval(0);
    }
    m_vsync = enabled;
  }

  //WINDOW TITLTE
  void Window::SetName(std::string name) {
    m_name = name;
    glfwSetWindowTitle((GLFWwindow*)m_window, name.c_str()); 
  }

  //Raw Input
  void Window::SetRawInput(bool enable) {
    glfwSetInputMode((GLFWwindow*)m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_enablecursor = enable;
  }

  //Enable Cursor
  void Window::SetEnableCursor(bool enable) {
    glfwSetInputMode((GLFWwindow*)m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    m_enablecursor = enable;
  }

  void Window::SetSize(unsigned int width, unsigned int height) {
    GLFWwindow* window = (GLFWwindow*)m_window;
    m_width = width;
    m_height = height;
    glfwSetWindowSize(window, width, height);
  }

  /*
   * METHODS 
   */

  //SWAP BUFFERS
  void Window::SwapBuffers() {
    glfwSwapBuffers((GLFWwindow*)m_window);
  }

  //SET AS CURRENT CONTEXT
  void Window::SetAsCurrentContext() const {
    glfwMakeContextCurrent((GLFWwindow*)m_window);
    //gladLoadGL();
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  }

  //TODO: implement gamepads and mouse
  const void Window::PollInput(Input& input) {
    glfwPollEvents();
    GLFWwindow* window = (GLFWwindow*)m_window;

    /* Uses keycodes defined in keycode.hpp (which reflect glfw). These keycodes
     * are ESSENTIAL for sbl::Input.GetKey(sbl::KeyCode)
     */
    for (int i = 0; i < Input::NUM_KEYS; i++) {
      input.KeyC[i] = glfwGetKey(window, i) == GLFW_PRESS ? true : false;
    }

    /* Mouse */
    //position
    double mX = 0;
    double mY = 0;
    glfwGetCursorPos(window, &mX, &mY);
    input.Mouse.xPos = mX; 
    input.Mouse.yPos = mY;

    //buttons
    input.Mouse.m1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ? true : false;
    input.Mouse.m2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ? true : false;
    input.Mouse.m3 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS ? true : false;
    input.Mouse.m4 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_4) == GLFW_PRESS ? true : false;
    input.Mouse.m5 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5) == GLFW_PRESS ? true : false;

    /* Gamepad */
    for (int i = 0; i < Input::NUM_GAMEPADS; i++) {
      GLFWgamepadstate state; 
      if (glfwGetGamepadState(i, &state)) {
        Input::Gamepad& gamepad = input.Gamepads[i];

        input.Gamepads[i].active = true;
        
        //buttons
        int numButtons; //not really used
        //const unsigned char* buttons = glfwGetJoystickButtons(i, &numButtons);
        const unsigned char* buttons = state.buttons;
        gamepad.up    = buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP];
        gamepad.down  = buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN];
        gamepad.left  = buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT];
        gamepad.right = buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT];

        gamepad.north = buttons[GLFW_GAMEPAD_BUTTON_Y];
        gamepad.south = buttons[GLFW_GAMEPAD_BUTTON_A];
        gamepad.west  = buttons[GLFW_GAMEPAD_BUTTON_X];
        gamepad.east  = buttons[GLFW_GAMEPAD_BUTTON_B];

        gamepad.leftBumper  = buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
        gamepad.rightBumper = buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER];

        gamepad.start  = buttons[GLFW_GAMEPAD_BUTTON_START];
        gamepad.select = buttons[GLFW_GAMEPAD_BUTTON_BACK];
        gamepad.home   = buttons[GLFW_GAMEPAD_BUTTON_GUIDE];

        gamepad.leftStickIn = buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB];
        gamepad.rightStickIn = buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB];

        //axes
        int numAxes;
        //const float* axes = glfwGetJoystickAxes(i, &numAxes);
        const float* axes = state.axes;
        gamepad.leftStick.x   = axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        gamepad.leftStick.y   = axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        gamepad.rightStick.x  = axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        gamepad.rightStick.y  = axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

        gamepad.leftTrigger = axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
        gamepad.rightTrigger = axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];
      }
    }

    /* Window Events */
    //resize
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    //WARNING: casting from int to unsigned int...
    input.WindowSize.width = windowWidth;
    input.WindowSize.height = windowHeight;
    //TODO: ANOTHER WARNING: should polling input change window size members automatically?
    m_width = windowWidth;
    m_height = windowHeight;
  }

  /*
   * STATIC METHODS
   */

  /* Initializes GLFW library
   */
  void Window::Init() { 
    //initialize GLFW
    glfwInit();
    //load gamepad mappings - WORKS!
    for (int i = 0; i < sizeof(sdl_gamepad_mappings) / sizeof(char*); i++) {
      glfwUpdateGamepadMappings(sdl_gamepad_mappings[i]); 
    }
  }
  
  void Window::Terminate() { 
    glfwTerminate();
  }
}


