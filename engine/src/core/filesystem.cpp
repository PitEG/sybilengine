#include "sybilengine/core/filesystem.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>

namespace sbl {

  FileSystem::ReadFile::ReadFile(void* io) 
  : m_io(io) {
  }

  FileSystem::ReadFile::~ReadFile() {
    Close();
  }

  unsigned long FileSystem::ReadFile::Read(std::vector<uint8_t>& buffer) {
    if (m_io == nullptr) { return -1; }
    return SDL_RWread((SDL_RWops*)m_io, (void*)buffer.data(), 1, buffer.size());
  }

  FileSystem::ReadFile FileSystem::OpenRead(std::string path) {
    SDL_RWops* io = SDL_RWFromFile(path.c_str(),"r");
    return FileSystem::ReadFile(io);
  }

  std::string FileSystem::ReadFile::ReadAllString() {
    std::string str;
    std::vector<uint8_t> buf(512);
    int bytes = 0;
    while((bytes = Read(buf)) > 0) {
      str.append(std::string(buf.begin(), buf.begin()+bytes));
    }
    return str;
  }

  void FileSystem::ReadFile::Close() {
    if (m_io != nullptr) {
      SDL_RWclose((SDL_RWops*)m_io);
    }
    m_io = nullptr;
  }

  FileSystem::WriteFile::WriteFile(void* io) 
  : m_io(io) {
  }

  FileSystem::WriteFile::~WriteFile() {
    Close();
  }

  FileSystem::WriteFile FileSystem::OpenWrite(std::string path) {
    SDL_RWops* io = SDL_RWFromFile(path.c_str(),"w");
    return FileSystem::WriteFile(io);
  }

  void FileSystem::WriteFile::Close() {
    if (m_io != nullptr) {
      SDL_RWclose((SDL_RWops*)m_io);
    }
    m_io = nullptr;
  }

  // TODO
  unsigned long FileSystem::WriteFile::Write(std::vector<uint8_t>& buffer, unsigned int amount) {
    return -1;
  }

  std::string FileSystem::GetExecPath() {
    char* pointer = SDL_GetBasePath();
    std::string path = std::string(pointer);
    // EXEC_PATH = path;
    SDL_free(pointer);
    return path;
  }

  std::string FileSystem::GetUserPath(std::string org, std::string app) {
    char* pointer = SDL_GetPrefPath(org.c_str(), app.c_str());
    std::string path = std::string(pointer);
    USER_PATH = path;
    SDL_free(pointer);
    return path;
  }

  std::string FileSystem::EXEC_PATH = GetExecPath();
  std::string FileSystem::USER_PATH = "";
}
