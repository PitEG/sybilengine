#pragma once

#include <string>
#include <vector>

/* 
 * I HAVE NO IDEA WHAT DO WITH FILESYSTEMS
 */
namespace sbl::fs {
  /*
   * PATH
   */
  // only uses UNIX like path formatting so no windows '\' for file names
  class Path {
  public:
    /*
     * Constructor
     */

    Path() : Path("") {}
    
    Path(std::string path);

    std::string ToString() const;

  private:
    std::string m_pathStr;

  //Static
  public:
    // provide the argv[0] and get the abs path to executable's directory
    static std::string GetExecPathStr(std::string path); //TODO rework this into the directory class
    static Path GetExecPath(std::string path);
  };

  /*
   * FILE 
   */
  class File {
  public:
    File();
    File(Path path);

    Path GetPath() const;
    std::string GetName() const;

  private:
    Path m_path;
  };

  /*
   * DIRECTORY
   */
  class Directory {
  public:

    Directory();
    Directory(Path path);

    Path GetPath() const;

    std::vector<Directory>  GetSubDirectories();
    std::vector<File>       GetFiles();
    File                    GetFileByName(std::string name);
  private:
    Path m_path;

  //Static Methods
  public:
    //feed argv[0] value and it returns the directory of the exec
    static Directory GetExecDirectory(char* argv);
  };


}
