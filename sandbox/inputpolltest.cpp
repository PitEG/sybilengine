#include "sybilengine/renderer/view.hpp"
#include "sybilengine/util/vector2.hpp"
#include <sybilengine/sybilengine.hpp>
#include <sybilengine/application.hpp>

class App : public sbl::Application {
public: 
  App() {
  }

  virtual ~App() override {
  }

  virtual void Start() override {
  }

  virtual void Run() override {
    sbl::Engine::Init(); 

    sbl::RenderWindow window("Sybil Render Window"); 
    window.SetAsCurrentContext();
    window.SetVsync(false);

    sbl::ImGuiContext imgui(window); //start an imgui context
    const std::string& win_name = window.Name();
    sbl::Logger::PrintLine(win_name);

    unsigned int frame = 0;
    int framerate = 300;
    double frametime = 1.0 / (double)framerate;

    double lastTime = sbl::Time::Now();

    sbl::BufferBits bufferbits;
    bufferbits.AddBit(sbl::BufferBit::ColorBit);
    while(window.IsOpen()) {
      sbl::Input input;
      window.PollInput(input);
      if (input.GetKey(sbl::KeyCode::Escape)) {
        window.Close();
      }

      window.Clear(bufferbits, sbl::Color(0.2f,0.2f,0.2f,0.2f));
      imgui.StartFrame();
      { //gamepad
        ImGui::Begin("Gamepads ");
        //bool jPressed = input.GetKey(sbl::KeyCode::F4);
        for (int i = 0; i < 16; i++) {
          const sbl::Input::Gamepad gamepad = input.Gamepads[i];
          bool active = gamepad.active;
          bool north  = gamepad.north;
          bool south  = gamepad.south;
          bool west   = gamepad.west;
          bool east   = gamepad.east;
          float lX = gamepad.leftStick.x;
          float lY = gamepad.leftStick.y;
          float rX = gamepad.rightStick.x;
          float rY = gamepad.rightStick.y;
          float lT = gamepad.leftTrigger;
          float rT = gamepad.rightTrigger;
          ImGui::Text("GAMEPAD %d", i + 1);
          ImGui::Checkbox("active", &active);
          ImGui::Checkbox("north is pressed", &north);
          ImGui::Checkbox("south is pressed", &south);
          ImGui::Checkbox("west is pressed", &west);
          ImGui::Checkbox("east is pressed", &east);
          ImGui::Text("left stick = x: %f, y: %f", lX, lY);
          ImGui::Text("right stick = x: %f, y: %f", rX, rY);
          ImGui::Text("left trigger = %f", lT);
          ImGui::Text("right trigger = %f", rT);
        }
        ImGui::End();
      }
      { //info and mouse
        ImGui::Begin("Info");
        ImGui::Text("x: %lf", input.Mouse.xPos);
        ImGui::Text("y: %lf", input.Mouse.yPos);
        bool m1 = input.Mouse.m1;
        bool m2 = input.Mouse.m2;
        bool m3 = input.Mouse.m3;
        bool m4 = input.Mouse.m4;
        bool m5 = input.Mouse.m5;
        ImGui::Checkbox("mouse button 1", &m1);
        ImGui::Checkbox("mouse button 2", &m2);
        ImGui::Checkbox("mouse button 3", &m3);
        ImGui::Checkbox("mouse button 4", &m4);
        ImGui::Checkbox("mouse button 5", &m5);
        ImGui::Text("frame: %u", frame);
        ImGui::Text("time: %fs", sbl::Time::Now());
        ImGui::End();
      }
      { //demo
        bool a = true;
        ImGui::ShowDemoWindow(&a); //temporary
      }
      imgui.RenderFrame();
      imgui.EndFrame();

      //swap buffers
      window.SwapBuffers();

      while (sbl::Time::Now() - lastTime < frametime) ;
      lastTime = sbl::Time::Now();
      frame++;
    }
  }

  virtual void Stop() override {
  }

};

void inputpolltest() {
  App app;
  app.Run();
}

int main() {
  inputpolltest();
  return 0;
}
