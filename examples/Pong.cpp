#include "Collider.h"
#include "Component.h"
#include "Engine.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "Transform.h"
#include <iostream>

// components/PaddleController.h
class PaddleController : public Component {
public:
  PaddleController(SDL_Keycode upKey, SDL_Keycode downKey, float speed)
      : upKey(upKey), downKey(downKey), speed(speed) {}

  void Update(float deltaTime) override { // Use overriding Update loop
    // We need access to input.
    // Since InputManager is private in Engine, and Engine handles Input.
    // We need a way to access Input.
    // For now, let's use SDL_GetKeyboardState directly for simplicity in this
    // example OR we should have exposed InputManager from Engine.

    // Let's use SDL directly for this component to avoid changing Engine too
    // much In a real engine, InputManager would be a Service or Singleton or
    // passed in.
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    Rigidbody *rb = owner->GetComponent<Rigidbody>();
    if (rb) {
      rb->SetVelocity(0, 0); // Reset velocity each frame for direct control

      if (state[SDL_GetScancodeFromKey(upKey)]) {
        rb->SetVelocity(0, -speed);
      } else if (state[SDL_GetScancodeFromKey(downKey)]) {
        rb->SetVelocity(0, speed);
      }
    }
  }

private:
  SDL_Keycode upKey;
  SDL_Keycode downKey;
  float speed;
};

// components/BallLogic.h
class BallLogic : public Component {
public:
  void Update(float deltaTime) override {
    Transform *t = owner->GetTransform();
    Vector2 pos = t->GetPosition();

    // Simple scoring check
    if (pos.x < 0) {
      std::cout << "Player 2 Scored!" << std::endl;
      ResetBall();
    } else if (pos.x > 800) {
      std::cout << "Player 1 Scored!" << std::endl;
      ResetBall();
    }
  }

  void ResetBall() {
    Transform *t = owner->GetTransform();
    t->SetPosition(400, 300);

    Rigidbody *rb = owner->GetComponent<Rigidbody>();
    if (rb) {
      // Randomize direction slightly
      float dirX = (rand() % 2 == 0) ? 1.0f : -1.0f;
      float dirY = ((rand() % 100) - 50) / 100.0f;
      rb->SetVelocity(dirX * 300, dirY * 300);
    }
  }
};

int main() {
  Engine engine;

  if (!engine.Init()) {
    return -1;
  }

  TextureManager *tm = nullptr;
  // We can't access TextureManager from here easily because it's private in
  // Engine. However, Sprite uses a static reference to it!

  // --- Create Paddle 1 (Left) ---
  auto p1 = std::make_unique<GameObject>("Player1");
  p1->GetTransform()->SetPosition(30, 300);
  p1->AddComponent<Sprite>()->SetDimensions(20, 100);
  // Note: Sprite will be pink since we didn't set texture, which is fine for
  // pong

  p1->AddComponent<PaddleController>(SDLK_w, SDLK_s, 400.0f);
  p1->AddComponent<Collider>(20, 100, ColliderType::DYNAMIC)
      ->SetBounciness(0.0f);

  // We use a Rigidbody but we want it to be "Kinematic" (controlled by script,
  // not physics forces usually) But our Physics engine handles all dynamic
  // bodies. Setting high mass or drag helps, or just setting velocity directly
  // (which we do).
  p1->AddComponent<Rigidbody>()->SetGravityScale(0.0f);

  engine.AddGameObject(std::move(p1));

  // --- Create Paddle 2 (Right) ---
  auto p2 = std::make_unique<GameObject>("Player2");
  p2->GetTransform()->SetPosition(770, 300);
  p2->AddComponent<Sprite>()->SetDimensions(20, 100);

  p2->AddComponent<PaddleController>(SDLK_UP, SDLK_DOWN, 400.0f);
  p2->AddComponent<Collider>(20, 100, ColliderType::DYNAMIC)
      ->SetBounciness(0.0f);
  p2->AddComponent<Rigidbody>()->SetGravityScale(0.0f);

  engine.AddGameObject(std::move(p2));

  // --- Create Ball ---
  auto ball = std::make_unique<GameObject>("Ball");
  ball->GetTransform()->SetPosition(400, 300);
  ball->AddComponent<Sprite>()->SetDimensions(20, 20);

  ball->AddComponent<Collider>(20, 20, ColliderType::DYNAMIC)
      ->SetBounciness(1.0f); // PERFECT bounce

  auto ballRb = ball->AddComponent<Rigidbody>();
  ballRb->SetGravityScale(0.0f);
  ballRb->SetVelocity(300, 200); // Start moving
  ballRb->SetDrag(0.0f);         // No air resistance
  ballRb->SetMass(1.0f);

  ball->AddComponent<BallLogic>();

  engine.AddGameObject(std::move(ball));

  // --- Create Top/Bottom Walls ---
  auto topWall = std::make_unique<GameObject>("TopWall");
  topWall->GetTransform()->SetPosition(400, -10);
  topWall->AddComponent<Collider>(800, 20, ColliderType::STATIC)
      ->SetBounciness(1.0f);
  engine.AddGameObject(std::move(topWall));

  auto botWall = std::make_unique<GameObject>("BotWall");
  botWall->GetTransform()->SetPosition(400, 610);
  botWall->AddComponent<Collider>(800, 20, ColliderType::STATIC)
      ->SetBounciness(1.0f);
  engine.AddGameObject(std::move(botWall));

  std::cout << "Starting Pong..." << std::endl;
  std::cout << "Controls: W/S for Left Paddle, UP/DOWN for Right Paddle"
            << std::endl;

  engine.Run();

  return 0;
}
