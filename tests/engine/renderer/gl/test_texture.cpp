#include <sybilengine/renderer/renderwindow.hpp>
#include <sybilengine/renderer/opengl/texture.hpp>
#include <sybilengine/sybilengine.hpp>
#include <catch2/catch_test_macros.hpp>

#include <iostream>

// https://www.glfw.org/docs/latest/context.html#context_offscreen <-- for creating an offscreen window in glfw

TEST_CASE("GL Texture Class", "[GLTexture]") {
  sbl::Engine::Init(); // initialize graphics library
  sbl::RenderWindow w;
  w.SetAsCurrentContext();

  SECTION("Blank Texture Constructors") {
  }

  sbl::Engine::Terminate(); // terminate graphcis library
}