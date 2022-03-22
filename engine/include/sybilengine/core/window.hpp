#pragma once 

#include <string>

#include "sybilengine/core/input.hpp" 
#include "sybilengine/renderer/opengl/bufferbits.hpp" 
#include "sybilengine/util/color.hpp" 
#include "sybilengine/util/vector2.hpp" 

namespace sbl {
  /**
   * @brief Operating system Window object.
   */
  class Window { 
  public:
    /**
     * @brief ImGuiContext needs to have access to Window backend implementation.
     */
    friend class ImGuiContext; // TODO NOT GOOD?
    /*
     * Constructors
     */

    /**
     * @brief Construct a new Window object. I think more than 1 can be opened,
     * but there isn't any context switching.
     * 
     * @param name Name of Window. By default, it's "Sybil Window".
     * @param width Width of the Window. 
     * @param height Height of the Window. 
     * @param resizeable If the window should be resizeable. 
     */
    Window(const std::string name = "Sybil Window", 
        const unsigned int width = 1280, 
        const unsigned int height = 720,
        const bool resizeable = true);

    /**
     * @brief Destroy the Window object.
     */
    virtual ~Window();

    /*
     * GETTERS
     */

    /**
     * @brief Get the name of the Window.
     * 
     * @return const std::string& Name of window.
     */
    inline std::string Name() const { return m_name; }
    /**
     * @brief Get the width of the Window.
     * 
     * @return unsigned int width of the Window in pixels.
     */
    inline unsigned int Width() const { return m_width; }
    /**
     * @brief Get the height of the Window.
     * 
     * @return unsigned int height of the Window in pixels.
     */
    inline unsigned int Height() const { return m_height; }
    //instead of a callback, there is a method do querry window size updates
    /**
     * @brief Poll Window object to update it's size.
     */
    void RefreshSize(); 
    /**
     * @brief Poll Window object to check if it's resizeable.
     */
    bool Resizeable();
    /**
     * @brief Poll the Window object to see if it should be closed.
     * 
     * @return true If the window should close.
     * @return false If the window should be open.
     */
    bool ShouldClose(); 
    /**
     * @brief Inverse of ShouldClose(). Checks if it should stil be open.
     * 
     * @return true If it should be open.
     * @return false If it should be closed.
     */
    bool IsOpen();

    /*
     * SETTERS
     */

    /**
     * @brief Turn on/off Vsync.
     * 
     * @param enable If Vsync should be enabled.
     */
    void SetVsync(bool enable);
    /**
     * @brief Set the Name of the window.
     * 
     * @param name The name to set the window.
     */
    void SetName(std::string name);
    /**
     * @brief Set the mouse to use raw input.
     * 
     * @param enable If the mouse input should use raw input.
     */
    void SetRawInput(bool enable);

    /**
     * @brief Set the mouse cursor's visibility
     * 
     * @param enable If the mouse cursor should be visible.
     */
    void SetEnableCursor(bool enable);

    /**
     * @brief Set the size of the Window.
     * 
     * @param width New width of the window.
     * @param height New height of the window.
     */
    void SetSize(unsigned int width, unsigned int height);

    /*
     * METHODS 
     */

    /** 
     * @brief Set this window as the current context (for drawing, inputs, etc.)
     */
    virtual void SetAsCurrentContext() const;
    /**
     * @brief polls input at an instance. sets m_input's values according to 
     * what keys are pressed, where mouse cursor is, etc. at this point 
     * in time. 
     * 
     * @param input The input object to populate with the new state info.
     */
    const void PollInput(Input& input); 

    /** 
     * @brief Swap window buffer
     */
    void SwapBuffers();

    /**
     * @brief Clears the window framebuffer.
     * 
     * @param bufferbits The buffers to clear.
     * @param color The color that the Color Buffer should be cleared with.
     */
    virtual void Clear(BufferBits bufferbits, Color color = Color(0,0,0,0)) {}

    /** 
     * @brief Set the close flag to true
     */
    inline void Close() { m_shouldClose = true; }

    /*
     * STATIC METHODS
     */

    /**
     * @brief Initializes external libraries that are needed for opening windows.
     * Should be done automatically when creating an Application object.
     */
    static void Init(); 
    /**
     * @brief Terminates external libraries that are needed for opening windows.
     * Should be done automatically when deleting an Application object.
     */
    static void Terminate(); 

  private:
    /**
     * @brief Flag for closing the window.
     */
    bool          m_shouldClose = false; 
    /**
     * @brief Vsync setting.
     */
    bool          m_vsync = false;
    /**
     * @brief Fullscreen setting.
     */
    bool          m_fullscren = false;
    /**
     * @brief Resizeable window setting.
     */
    bool          m_resizeable = true;
    /**
     * @brief Mouse raw input setting.
     */
    bool          m_rawinput = true;
    /**
     * @brief Mouse cursor visible setting.
     */
    bool          m_enablecursor = true;
    /**
     * @brief Name of window.
     */
    std::string   m_name; 
    /**
     * @brief Width of window.
     */
    unsigned int  m_width;
    /**
     * @brief Height of window.
     */
    unsigned int  m_height;

    /**
     * @brief For now should be GLFWwindow* but I don't want to explicitly write that.
     */
    void* m_window; 

    /**
     * @brief Input events of this window object. I think it's DEPRECATED.
     */
    Input m_input;  

  };
}
