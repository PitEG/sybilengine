#pragma once 

#include "sybilengine/sybilengine.hpp"
#include "sybilengine/core/filesystem.hpp"

#include <string>

namespace sbl {
  /**
   * @brief This is the entry point for the game engine. It will initialize
   * external libraries and sybilengine things for you if you inherit from it.
   */
  class Application {
  public:
    /**
     * @brief Sets the executable directory for the FileSystem module.
     * 
     * @param dir The directory.
     */
    void SetExecDir(fs::Directory dir);
    /**
     * @brief Passes the argvs from the main() function.
     * 
     * @param argv Argument values
     * @param argc Argument count
     */
    virtual void PassArgv(char* argv[], unsigned int argc);

  protected:
    /**
     * @brief Construct a new Application object. It is also where
     * external libraries and sybilengine things are initialized. 
     * When objects inherit from this class, it will also call this constructor.
     */
    Application();
    /**
     * @brief Destroy the Application object. It also terminates initialized
     * external libraries and sybilengine stuff.
     */
    virtual ~Application();

    /**
     * @brief Should have a Start function.
     */
    virtual void Start() = 0;
    /**
     * @brief Should have a Start function.
     */
    virtual void Run() = 0;
    /**
     * @brief Should have a Start function.
     */
    virtual void Stop() = 0;
  
  protected:
    Window* m_window; //probably optional
    fs::Directory m_execDirectory;
  };
}
