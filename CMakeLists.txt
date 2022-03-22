cmake_minimum_required(VERSION 3.17)

option(BUILD_WINDOWS "Build for Windows")
option(BUILD_LINUX "Build for Windows")

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-fno-stack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(sybil)

#[[
if(BUILD_WINDOWS)
# DOESN'T WORK
  message("Building for Windows!")
  set(CMAKE_SYSTEM_NAME Windows)

  SET(CMAKE_FIND_ROOT_PATH /usr/i686-mingw32)

  SET(CMAKE_C_COMPILER    i686-w64-mingw32-gcc)
  SET(CMAKE_CXX_COMPILER  i686-w64-mingw32-g++)
  SET(CMAKE_RC_COMPILER   i686-w64-mingw32-windres)
  set(CMAKE_RANLIB i686-w64-mingw32-ranlib)

  set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

endif(BUILD_WINDOWS)
]]

if(BUILD_LINUX)
endif(BUILD_LINUX)

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(sandbox)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_subdirectory(tests)
endif()
