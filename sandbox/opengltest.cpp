#include <sybilengine/sybilengine.hpp>
#include <sybilengine/application.hpp>

#include <string>
#include <vector>

// STRUCTS
struct Menu {
  float desired_fps = 60.0;
  int radio = 0;

};

struct Camera {
  float speed = 32.f;
};

struct Demo {
  void Render(const sbl::Input& input, const float delta_time) {
  }
};

// ROUTINES
void move_camera(sbl::View& view, const sbl::Input& input, const Camera& camera, const float delta_time) {
  const float speed = camera.speed;
  sbl::Vector2 direction = sbl::Vector2::Zero();
  if (input.GetKey(sbl::KeyCode::E)) {
    direction += sbl::Vector2::Up();
  }
  if (input.GetKey(sbl::KeyCode::D)) {
    direction += sbl::Vector2::Down();
  }
  if (input.GetKey(sbl::KeyCode::S)) {
    direction += sbl::Vector2::Left();
  }
  if (input.GetKey(sbl::KeyCode::F)) {
    direction += sbl::Vector2::Right();
  }
  view.Move(direction * delta_time * speed);
}

// APPLICATION
class App : public sbl::Application {
public:
  void Start() override {
    window.SetAsCurrentContext();
  }

  void Run() override {
    //Renderer
    sbl::Renderer renderer;

    //screen Sprite
    sbl::Texture fbTexture(window.Width(), window.Height());
    sbl::Sprite framebuffer(&fbTexture);

    //Sybil Sprite
    sbl::fs::File sybilFile = m_execDirectory.GetFileByName("sybil.png");
    sbl::Texture sybilTexture(sybilFile.GetPath().ToString(), sbl::ImageFileType::PNG);
    sbl::Sprite sybilSprite(&sybilTexture, sbl::Color::White());
    sybilSprite.color = sbl::Color(1,1,1,1);
    sybilSprite.transform.Rotate(0);
    sybilSprite.SetTextureCoords(sbl::Rect(sbl::Vector2(0,0), sbl::Vector2(16,16)) );

    //view 
    sbl::View view(sbl::Rect(sbl::Vector2(0, 0), sbl::Vector2(window.Width(), window.Height())));
    view.Move(-sbl::Vector2(window.Width()/2, window.Height()/2));
    sbl::View screenView(sbl::Rect(sbl::Vector2::Zero(), sbl::Vector2(window.Width(), window.Height())));
    float view_size = 1.f;
    Camera camera;

    // screen view
    sbl::Rect screenRect(sbl::Vector2(0,0), sbl::Vector2(window.Width(), window.Height()));

    //Imgui
    sbl::ImGuiContext imgui(window);

    //graphics loop
    sbl::BufferBits bufferbits;
    bufferbits.AddBit(sbl::BufferBit::ColorBit);
    window.SetVsync(false); //vsync

    double startTime = sbl::Time::Now();
    double lastFrameTime = sbl::Time::Now();
    double frameTime;

    Menu menu;

    while(window.IsOpen()) {
      double desiredFrameTime = 1.0 / menu.desired_fps;
      frameTime = sbl::Time::Now() - lastFrameTime;
      float deltaTime = frameTime;
      lastFrameTime = sbl::Time::Now();

      //poll input
      window.PollInput(input);
      if(input.GetKey(sbl::KeyCode::Escape)) {
        window.Close();
      }

      // camera movement 
      move_camera(view, input, camera, deltaTime);

      // clear framebuffers
      window.Clear(bufferbits,sbl::Color(.1f,.1f,.1f,1));
      renderer.Clear(fbTexture, sbl::Color(0,0,0,0));

      // temp drawing
      std::vector<sbl::Sprite> sprites{sybilSprite};
      renderer.Draw(sprites, view, framebuffer, &sybilTexture);
      renderer.DrawToScreen(framebuffer, screenRect);

      // Main Menu
      imgui.StartFrame();
      ImGui::Begin("interface");
      ImGui::SliderFloat("target fps", &menu.desired_fps, 30.f, 2000.f,"%1.f");
      ImGui::Text("%lf fps", 1 / frameTime);
      ImGui::Text("frame time: %lfs", frameTime);
      if (ImGui::TreeNode("Camera")) {
        ImGui::SliderFloat("Zoom", &view_size, 0.10f, 2.00f,"%.01f");
        ImGui::SliderFloat("Speed", &camera.speed, 32.f, 256.f,"%.01f");
        ImGui::TreePop();
      }
      ImGui::Text("radio");
      ImGui::RadioButton("many sprites",&menu.radio, 0);
      ImGui::RadioButton("blending",&menu.radio, 1);
      ImGui::RadioButton("animation",&menu.radio, 2);
      ImGui::End();
      imgui.RenderFrame();
      imgui.EndFrame();

      window.SwapBuffers();

      while (sbl::Time::Now() < startTime + desiredFrameTime) {
        const double waitTime = 0.00001;
        sbl::Time::Wait(waitTime);
      }
      // do not put any lengthy process between these two lines
      startTime += desiredFrameTime;
    }
  }

  void Stop() override {
  }

private:
  sbl::Input        input;
  sbl::RenderWindow window = sbl::RenderWindow("OpenGl Test", 1280, 720, false);
};

int main(int argc, char* argv[]) {
  //opengl test
  App app;
  app.PassArgv(argv, argc);
  app.Start();
  app.Run();
  app.Stop();
}
