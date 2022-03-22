#include "sybilengine/core/filesystem.hpp"

#include <filesystem>

namespace sbl::fs {
  /*
   * Directory
   */
  Directory::Directory(Path path) : m_path(path) {}
  Directory::Directory() :          m_path(Path()) {}

  Path Directory::GetPath() const {
    return m_path;
  }

  std::vector<Directory> Directory::GetSubDirectories() {
    std::vector<Directory> dirs;
    for(auto& p: std::filesystem::directory_iterator(m_path.ToString().c_str())){
      //if sub file is a directory
      if(std::filesystem::is_directory(p)) {
        std::string pathStr = p.path().string();
        Path path = Path(pathStr);
        Directory dir = Directory(path);
        dirs.push_back(dir);
      }
    }
    return dirs;
  }

  std::vector<File> Directory::GetFiles() {
    std::vector<File> files;
    for(auto& p: std::filesystem::directory_iterator(m_path.ToString().c_str())){
      //if sub file is a directory
      if(std::filesystem::is_regular_file(p)) {
        std::string pathStr = p.path().string();
        Path path = Path(pathStr);
        File file = File(path);
        files.push_back(file);
      }
    }
    return files;
  }

  File Directory::GetFileByName(std::string name) {
    std::vector<File> files;
    for(auto& p: std::filesystem::directory_iterator(m_path.ToString().c_str())){
      //if sub file is a regular file
      if(std::filesystem::is_regular_file(p)) {
        std::string pathStr = p.path().filename();
        //if file is matching name, return it
        if (pathStr == name) {
          File found = File(p.path().string());
          return found;
        }
      }
    }

    //file not found, return a file that doesn't point to anything
    return File();
  }

  //static stuff
  Directory Directory::GetExecDirectory(char* argv) {
    auto dir =  
      std::filesystem::weakly_canonical(std::filesystem::path(argv))
      .parent_path();
    std::string dirStr = dir.c_str();
    Path dirPath = Path(dirStr);
    return Directory(dirPath);
  }


  /*
   * File
   */
  File::File() : m_path(Path()) {}
  File::File(Path path) : m_path(path) {}

  Path File::GetPath() const {
    return m_path;
  }

  std::string File::GetName() const {
    std::string fullPath = m_path.ToString();
    std::filesystem::path path(fullPath);
    std::string name = path.filename();

    return name;
  }

  /*
   * Path
   */
  Path::Path(std::string path) {
    m_pathStr = path;
  }

  std::string Path::ToString() const {
    return m_pathStr;
  }

  //static path
  std::string Path::GetExecPathStr(std::string path) {
    const char *cstr = path.c_str();
    auto dir = 
      std::filesystem::weakly_canonical(std::filesystem::path(cstr))
      .parent_path();
    path = dir.c_str();
    return path;
  }
}
