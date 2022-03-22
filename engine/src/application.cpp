#include "sybilengine/application.hpp"
#include "sybilengine/sybilengine.hpp"

namespace sbl {
  Application::Application() {
    Engine::Init();
  }

  Application::~Application() {
    Engine::Terminate();
  }

  void Application::PassArgv(char* argv[], unsigned int argc) {
    fs::Directory execDir = fs::Directory::GetExecDirectory(argv[0]);
    SetExecDir(execDir);
  }

  void Application::SetExecDir(fs::Directory dir) {
    m_execDirectory = dir;
  }
}
