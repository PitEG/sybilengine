cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_FLAGS "-fno-stack-protector") # stack canaries
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(sybil)

add_subdirectory(engine)
add_subdirectory(sandbox)
# add_subdirectory(editor)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  # add_subdirectory(tests)
endif()
