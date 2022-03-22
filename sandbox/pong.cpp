#include <sybilengine/sybilengine.hpp>
#include <sybilengine/application.hpp>

#include <vector>

class Pong : public sbl::Application {
public:
  void UpdateSpriteTransforms(sbl::Scene& scene) {
    auto& transformsCM = scene.GetComponents<sbl::Transform>();
    auto& spritesCM = scene.GetComponents<sbl::Sprite>();

    for (auto& component : spritesCM) {
      sbl::Component<sbl::Transform>* transform = transformsCM[component.GetEntity()];
      if (transform) {
        component.data.transform = transform->data;
      }
    }
  }

  void UpdatePosition(sbl::Scene& scene, sbl::Input& input, sbl::Entity& p1, sbl::Entity& p2) {
    sbl::Vector2 velocity1;
    if (input.GetKey(sbl::KeyCode::W)) {
      velocity1 = velocity1 + sbl::Vector2::Up();
    }
    if (input.GetKey(sbl::KeyCode::S)) {
      velocity1 = velocity1 + sbl::Vector2::Down();
    }

    sbl::Vector2 velocity2;
    if (input.GetKey(sbl::KeyCode::Up)) {
      velocity2 = velocity2 + sbl::Vector2::Up();
    }
    if (input.GetKey(sbl::KeyCode::Down)) {
      velocity2 = velocity2 + sbl::Vector2::Down();
    }

    sbl::Vector2& pos1 = scene.GetComponents<sbl::Transform>().Get(p1)->data.position;
    sbl::Vector2& pos2 = scene.GetComponents<sbl::Transform>().Get(p2)->data.position;
    pos1 = pos1 + velocity1;
    pos2 = pos2 + velocity2;
  }

  void UpdateCollisionBoxes(sbl::Scene& scene) {
    sbl::ComponentManager<sbl::Transform>& transformsCM = scene.GetComponents<sbl::Transform>();
    sbl::ComponentManager<sbl::Collider>& collidersCM = scene.GetComponents<sbl::Collider>();

    for (auto& component : collidersCM) {
      sbl::Transform& t = transformsCM.Get(component.GetEntity())->data;
      component.data.SetPosition(t.position);
    }
  }

  typedef sbl::Vector2 Velocity;

  void UpdateBallVelocity(sbl::Scene& scene, sbl::Entity& ball, sbl::Entity& p1, sbl::Entity& p2) {
    sbl::Vector2& ballPos = scene.GetComponents<sbl::Transform>().Get(ball)->data.position;
    sbl::Vector2& ballVelocity = scene.GetComponents<Velocity>().Get(ball)->data;
    float speed = ballVelocity.Magnitude();

    if (ballVelocity == sbl::Vector2::Zero()) {
      ballVelocity = Velocity(1,0);
    }

    sbl::CollisionMatrix cm;
    cm.AddCollision(1,0);
    cm.AddCollision(0,1);

    auto& collidersCM = scene.GetComponents<sbl::Collider>();
    std::vector<sbl::Collider*> colliders;
    for(auto& component : collidersCM) {
      colliders.push_back(&component.data);
    }
    sbl::Collider::CalculateCollisions(colliders,cm);

    sbl::Collider& ballCollider = collidersCM.Get(ball)->data;
    std::vector<sbl::Collision>& ballCollisions = ballCollider.GetCollisions();
    static sbl::Random random;
    float angle = random.RangeFloat(sbl::Math::PI / 2) - (sbl::Math::PI / 4);
    for (int i = 0; i < ballCollisions.size(); i++) {
      const sbl::Entity& collidingEntity = ballCollisions[i].GetCollider().GetEntity();
      if (collidingEntity == p1) {
        ballVelocity = sbl::Vector2(angle) * speed * 1.05;
      }
      if (collidingEntity == p2) {
        ballVelocity = sbl::Vector2(angle) * speed * -1 * 1.05;
      }
    }
    
    if (ballPos.y > 144 || ballPos.y < 0) {
      ballVelocity.y = -ballVelocity.y;
    }

    if (ballPos.x > 256 || ballPos.x < 0) {
      ballVelocity.x = -ballVelocity.x;
    }

    ballPos = ballPos + ballVelocity;
  }

  void Start() override {
    window.SetAsCurrentContext();
  }

  void Run() {
    sbl::ImGuiContext imgui(window);

    // Sprites
    sbl::Renderer renderer;
    sbl::Texture white(1,1);
    renderer.Clear(white, sbl::Color(1,1,1,1));
    sbl::Sprite paddleSprite(&white);
    sbl::Sprite ballSprite = paddleSprite;
    sbl::Rect paddleRect(sbl::Vector2(0,0), sbl::Vector2(8,60));
    paddleSprite.SetTextureCoords(paddleRect);
    sbl::Rect ballRect(sbl::Vector2(0,0), sbl::Vector2(4,4));
    ballSprite.SetTextureCoords(ballRect);

    // screen
    sbl::Texture fbTexture(256, 144);
    sbl::Sprite framebuffer(&fbTexture);
    //view 
    sbl::View view(sbl::Rect(sbl::Vector2(0, 0), sbl::Vector2(256, 144)));
    sbl::View screenView(sbl::Rect(sbl::Vector2::Zero(), sbl::Vector2(window.Width(), window.Height())));
    // screen view
    sbl::Rect screenRect(sbl::Vector2(0,0), sbl::Vector2(window.Width(), window.Height()));

    //Game Logic
    sbl::Scene scene;
    int player1Score = 0;
    int player2Score = 0;

    sbl::Entity p1 = scene.CreateEntity();
    sbl::Entity p2 = scene.CreateEntity();
    sbl::Entity ball = scene.CreateEntity();

    scene.AddComponent<sbl::Sprite>(p1, paddleSprite);
    scene.AddComponent<sbl::Sprite>(p2, paddleSprite);
    scene.AddComponent<sbl::Sprite>(ball, ballSprite);

    sbl::Collider p1Collider(paddleRect, 0, p1);
    sbl::Collider p2Collider(paddleRect, 0, p2);
    sbl::Collider bCollider(ballRect, 1);

    scene.AddComponent<sbl::Collider>(p1, p1Collider);
    scene.AddComponent<sbl::Collider>(p2, p2Collider);
    scene.AddComponent<sbl::Collider>(ball, bCollider);

    scene.AddComponent<Velocity>(ball,Velocity());

    scene.GetComponents<sbl::Transform>().Get(p1)->data.position = sbl::Vector2(20,72);
    scene.GetComponents<sbl::Transform>().Get(p2)->data.position = sbl::Vector2(230,72);
    scene.GetComponents<sbl::Transform>().Get(ball)->data.position = sbl::Vector2(128,72);

    while (window.IsOpen()) {
      // poll input
      window.PollInput(input);
      if (input.GetKey(sbl::KeyCode::Escape)) {
        window.Close();
      }

      // Game Logic
      UpdatePosition(scene,input,p1,p2);
      UpdateSpriteTransforms(scene);
      UpdateCollisionBoxes(scene);
      UpdateBallVelocity(scene, ball,p1,p2);
      const std::vector<sbl::Component<sbl::Sprite>> spritesP = scene.GetComponents<sbl::Sprite>().GetComponents();
      std::vector<sbl::Sprite> sprites(spritesP.size());
      for (int i = 0; i < sprites.size(); i++) {
        sprites[i] = spritesP[i].data;
      }

      // Draw
      sbl::BufferBits bb;
      bb.AddBit(sbl::BufferBit::ColorBit);
      window.Clear(bb, sbl::Color(0,0,0,1));

      renderer.Clear(fbTexture,sbl::Color(0,0,0,1));
      renderer.Draw(sprites, view, framebuffer, &white);
      renderer.DrawToScreen(framebuffer, screenRect);

      // Draw ImGuiStuff
      imgui.StartFrame();
      ImGui::Begin("SCOREBOARD");

      ImGui::Text("Player 1 Score: %d", player1Score);
      sbl::Vector2 player1Pos = scene.GetComponents<sbl::Transform>().Get(p1)->data.position;
      sbl::Vector2 player1CPos = scene.GetComponents<sbl::Collider>().Get(p1)->data.GetRect().Center();
      ImGui::Text("Player 1 position: x = %f, y = %f", player1Pos.x, player1Pos.y);
      ImGui::Text("Player 1 collision center: x = %f, y = %f", player1Pos.x, player1Pos.y);

      ImGui::Text("Player 2 Score: %d", player2Score);
      sbl::Vector2 player2Pos = scene.GetComponents<sbl::Transform>().Get(p1)->data.position;
      sbl::Vector2 player2CPos = scene.GetComponents<sbl::Collider>().Get(p2)->data.GetRect().Center();
      ImGui::Text("Player 2 position: x = %f, y = %f", player2Pos.x, player2Pos.y);
      ImGui::Text("Player 2 collision center: x = %f, y = %f", player1CPos.x, player1CPos.y);

      sbl::Vector2 ballPos = scene.GetComponents<sbl::Transform>().Get(ball)->data.position;
      ImGui::Text("Ball Pos: x = %f, y = %f", ballPos.x, ballPos.y);

      ImGui::End();
      imgui.RenderFrame();
      imgui.EndFrame();

      // swap buffer
      window.SwapBuffers();
    }
  }

  void Stop() {

  }

private:
  sbl::Input        input;
  sbl::RenderWindow window = sbl::RenderWindow("\"Ping\"", 1280, 720, false);
};


int main () {
  Pong pong;

  pong.Start();
  pong.Run();
  pong.Stop();

  return 0;
}
