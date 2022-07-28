project(sybilsandbox)

# core processes 
add_executable(core core.cpp)
target_link_libraries(core PRIVATE sybilengine)
