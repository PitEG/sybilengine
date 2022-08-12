#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace sbl {
  class FileSystem;
  using FS = FileSystem;
  using byte = uint8_t;

  class FileSystem {
  public:
    class ReadFile {
    friend class FileSystem;
    public:
      ~ReadFile();

      unsigned long Size();
      unsigned long Read(std::vector<byte>& buffer);
      std::string ReadAllString();

      void Close();

    private:
      ReadFile(void* m_io);
      void* m_io;
    };

    class WriteFile {
    friend class FileSystem;
    public:
      ~WriteFile();

      unsigned long Write(std::vector<byte>& buffer, unsigned int amount);
      void Close();

    private:
      WriteFile(void* m_io);
      void* m_io;
    };

    static std::string GetExecPath(); // this also caches results in EXEC_PATH
    static std::string GetUserPath(std::string org, std::string app); // this also caches results in USER_PATH

    static ReadFile OpenRead(std::string path);
    static WriteFile OpenWrite(std::string path);

    static std::string EXEC_PATH;
    static std::string USER_PATH;
  };
}
