#include <sybilengine/sybilengine.hpp>
#include <sybilengine/application.hpp>
#include <string>
#include <vector>

struct Boxes {
  std::vector<sbl::RectangleShape> rectangles;
  std::vector<sbl::Collider> colliders;
  std::vector<sbl::Vec2f> velocities;
  std::vector<std::vector<sbl::Collision>> collisions;
  std::vector<int> selected;
  std::vector<int> ids;
};

class App : public sbl::Application {
public:
  sbl::RenderWindow window;
  void Start() override {
    window.SetAsCurrentContext();
    window.SetVsync(false);
  }
  void Stop() override {
  }
  void Run() override {
    sbl::Renderer renderer;
    sbl::Texture framebuffer_texture(window.Width(),window.Height());
    sbl::Sprite framebuffer(&framebuffer_texture);
    sbl::Rect screen_rect(sbl::Vec2f::Zero(), sbl::Vec2f(window.Width(),window.Height()));
    sbl::View view(sbl::Rect(0,0,window.Width(),window.Height()));
    sbl::Random random(1);

    // collider grid
    const int grid_width = 30;
    const int grid_height = 30;
    sbl::ColliderGrid grid(sbl::Rect(0,0,window.Width(),window.Height()),grid_width,grid_height);

    // grid lines
    std::vector<sbl::LineShape> lines;

    for (int i = 0; i <= grid_width; i++) {
      float x = (float) window.Width() / (float) grid_width * i;
      sbl::LineShape line(
        sbl::Vec2f(x,0),
        sbl::Vec2f(x,window.Height()));
      lines.push_back(line);
    }
    for (int i = 0; i <= grid_width; i++) {
      float y = (float) window.Height() / (float) grid_height * i;
      sbl::LineShape line(
        sbl::Vec2f(0,y),
        sbl::Vec2f(window.Width(),y));
      lines.push_back(line);
    }

    // make all rectangles
    Boxes boxes;
    sbl::Logger::PrintLine("making boxes...");
    const int num_boxes = 16000;
    const int box_size = 3;
    for (int i = 0; i < num_boxes; i++) {
      // shape
      float x = random.RangeFloat(window.Width());
      float y = random.RangeFloat(window.Height());
      sbl::Transform t(sbl::Vec2f(x,y),0,0);
      sbl::Vec2f size(box_size,box_size);
      sbl::RectangleShape rectshape(t,size);
      boxes.rectangles.push_back(rectshape);
      
      // colliders
      sbl::Collider collider(sbl::Rect(t.position,size),0);
      boxes.colliders.push_back(collider);

      // velocity
      float angle = random.RangeFloat(sbl::Math::PI * 2);
      x = sbl::Math::Cos(angle);
      y = sbl::Math::Sin(angle);
      boxes.velocities.push_back(sbl::Vec2f(x,y));

      // collider grid id
      int id = grid.Add(collider);
      boxes.ids.push_back(id);

      // collision list
      std::vector<sbl::Collision> collisions;
      boxes.collisions.push_back(collisions);

      // selected
      boxes.selected.push_back(false);
    }

    sbl::Input input;
    float speed = 5.f;

    sbl::BufferBits buffer_bits;

    sbl::ImGuiContext imgui(window);

    buffer_bits.AddBit(sbl::BufferBit::ColorBit);
    float desired_framerate = 60;
    double frame_time = 0;
    double start_frametime = sbl::Time::Now();
    double last_frametime = sbl::Time::Now();
    
    bool paused = false;

    std::vector<std::vector<int>> cell_info;
    
    bool color_setting = true;
    std::vector<sbl::Color> colors;
    for (int i = 0; i < grid_width; i++) {
      for (int j = 0; j < grid_height; j++) {
        float r_normalize = (float)(grid_width - i) / (float)(grid_width);
        float g_normalize = (float)(grid_height - i) / (float)(grid_width);
        float b_normalize = (float)(grid_height - j) / (float)(grid_height);
        colors.push_back(sbl::Color(r_normalize,1-g_normalize,b_normalize,1));
      }
    }

    sbl::Logger::PrintLine("starting loop...");
    std::vector<sbl::Collision> collisions;
    collisions.reserve(20);
    while (window.IsOpen()) {
      double desired_frametime = (double) 1 / desired_framerate;
      frame_time = sbl::Time::Now() - last_frametime;
      last_frametime = sbl::Time::Now();

      
      sbl::Color bg_color(0.1f,0.1f,0.1f,1.f);
      window.Clear(buffer_bits, sbl::Color::White());
      renderer.Clear(framebuffer_texture, bg_color);

      //INPUT
      window.PollInput(input);
      if (input.GetKey(sbl::KeyCode::Escape)) {
        window.Close();
      }
      if (input.GetKey(sbl::KeyCode::E)) { view.Move(sbl::Vec2f::Up()    * speed); }
      if (input.GetKey(sbl::KeyCode::D)) { view.Move(sbl::Vec2f::Down()  * speed); }
      if (input.GetKey(sbl::KeyCode::S)) { view.Move(sbl::Vec2f::Left()  * speed); }
      if (input.GetKey(sbl::KeyCode::F)) { view.Move(sbl::Vec2f::Right() * speed); }

      //PHYSICS

      if (!paused) {
        for (int i = 0; i < boxes.rectangles.size(); i++) {
          sbl::RectangleShape& shape = boxes.rectangles[i];
          sbl::Vec2f& velocity = boxes.velocities[i];
          sbl::Collider& collider = boxes.colliders[i];
          int id = boxes.ids[i];
          shape.GetTransform().Translate(velocity);

          // correct if hitting bounds
          sbl::Vec2f position = shape.GetTransform().position;
          if (position.x < 0 || position.x > window.Width()) {
            velocity.x = -velocity.x;
          }
          if (position.y < 0 || position.y > window.Height()) {
            velocity.y = -velocity.y;
          }

          // set new position
          collider.SetPosition(position);
          // sbl::Logger::PrintLine("curr id:" + std::to_string(i));
          grid.Modify(id,collider);
        }
      }
      // COLORING
      if (color_setting) {
        grid.GetCellInfo(cell_info);
        for (int i = 0; i < cell_info.size(); i++) {
          float color_value = (float) (cell_info.size() - i) / (float) cell_info.size();
          for (int j = 0; j < cell_info[i].size(); j++) {
            int id = (cell_info[i])[j];
            boxes.rectangles[id].color = colors[i];
          }
        }
      }
      else {
        for (int id = 0; id < num_boxes; id++) {
          // turn red if colliding with another box 
          auto& collisions = boxes.collisions[id];
          grid.GetCollisions(id,collisions);
          bool colliding = collisions.size() > 0;
          if (colliding) { boxes.rectangles[id].color = sbl::Color(1,0,0,1); }
          else { boxes.rectangles[id].color = sbl::Color::White(); }
        }
      }
      /*
      for (int id = 0; id < num_boxes; id++) {
        if (boxes.selected[id]) {
          boxes.rectangles[id].color = sbl::Color(1,0,0,1);
        }
        else {
          boxes.rectangles[id].color = sbl::Color::White();
        }
      }
      */

      //RENDER
      renderer.Draw(lines, view, framebuffer);
      renderer.Draw(boxes.rectangles, view, framebuffer);
      renderer.DrawToScreen(framebuffer, screen_rect);

      imgui.StartFrame();
      ImGui::Begin("framerate");
      ImGui::Text("frame rate: %lfs", (double) 1 / frame_time);
      ImGui::Text("frame time: %lfs", frame_time);
      ImGui::SliderFloat("framerate", &desired_framerate, 30.f, 2000.f, "%1.f");
      ImGui::Checkbox("pause", &paused);
      ImGui::Checkbox("color setting", &color_setting);
      if (ImGui::CollapsingHeader("Cell Info")) {
        for (int i = 0; i < cell_info.size(); i++) {
          ImGui::Text("cell #%d size:%d", i, cell_info[i].size());
        }
      }
      if (ImGui::CollapsingHeader("Box Info")) {
        for (int i = 0; i < num_boxes; i++) {
          sbl::Vec2f position = boxes.rectangles[i].GetTransform().position;
          ImGui::Checkbox("select", (bool*)(&boxes.selected[i]));
          ImGui::Text("box #%d: x=%f,y=%f",i,position.x, position.y);
          sbl::Vec2f size = boxes.colliders[i].GetRect().Size();
          sbl::Vec2f collider_position = boxes.colliders[i].GetRect().BR() - (sbl::Vec2f(1,1) * box_size / 2);
          ImGui::Text("collider position: x=%f,y=%f",collider_position.x,collider_position.y);
          ImGui::Text("collider size: %fx%f",size.x,size.y);
          ImGui::Text("num collisions: %d",boxes.collisions[i].size());
        }
      }
      ImGui::End();
      imgui.RenderFrame();
      imgui.EndFrame();

      window.SwapBuffers();

      while (sbl::Time::Now() < start_frametime + desired_frametime) {
        sbl::Time::Wait(0.0001);
      }
      start_frametime += desired_frametime;
    }
  }
};

int main(int argc, char* argv[]) {
  //opengl test
  App app;
  app.PassArgv(argv, argc);
  app.Start();
  app.Run();
  app.Stop();
}
