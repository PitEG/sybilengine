#include <sybilengine/sybilengine.hpp>
#include <sybilengine/application.hpp>

//#include <iostream>

class App : public sbl::Application {
public: 
  App() {
    m_window = new sbl::Window("something");
  }

  virtual ~App() override {
    delete m_window;
  }

  virtual void Start() override {
    m_window->SetAsCurrentContext();
  }

  virtual void Run() override {
    sbl::Color clearColor(0.5f, 0.5f, 0.1f, 1.0f);
    sbl::BufferBits bufferbits;
    bufferbits.AddBit(sbl::BufferBit::ColorBit);
    while (!m_window->ShouldClose()) {
      m_window->Clear(bufferbits, clearColor);
      sbl::Input input;
      m_window->PollInput(input);
      if (input.GetKey(sbl::KeyCode::Escape)) {
        m_window->Close();
      }

      m_window->SwapBuffers();
    }
  }

  virtual void Stop() override {
  }

};

int main() {
  App* app = new App();
  app->Start();
  app->Run();
  app->Stop();

  delete app;
  return 0;
}
