#include "Collider.h"
#include "Component.h"
#include "Engine.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "Text.h"
#include "Transform.h"
#include <iostream>
#include <random>
#include <string>

static int p1Score = 0;
static int p2Score = 0;
static GameObject *p1ScoreGO = nullptr;
static GameObject *p2ScoreGO = nullptr;

static void updateScores() {
    if (p1ScoreGO)
        p1ScoreGO->GetComponent<Text>()->SetText(std::to_string(p1Score));
    if (p2ScoreGO)
        p2ScoreGO->GetComponent<Text>()->SetText(std::to_string(p2Score));
}

// ---- Paddle Controller ------------------------------------------------
class PaddleController : public Component {
public:
    PaddleController(SDL_Keycode upKey, SDL_Keycode downKey, float speed)
        : upKey(upKey), downKey(downKey), speed(speed) {}

    void Update(float deltaTime) override {
        InputManager *input = InputManager::Get();
        if (!input) return;

        Rigidbody *rb = owner->GetComponent<Rigidbody>();
        if (!rb) return;

        rb->SetVelocity(0, 0);
        if (input->IsKeyHeld(upKey))   rb->SetVelocity(0, -speed);
        else if (input->IsKeyHeld(downKey)) rb->SetVelocity(0, speed);
    }

private:
    SDL_Keycode upKey, downKey;
    float       speed;
};

// ---- Ball Logic -------------------------------------------------------
class BallLogic : public Component {
public:
    void Update(float deltaTime) override {
        Transform *t   = owner->GetTransform();
        Vector2    pos = t->GetPosition();

        if (pos.x < 0) {
            p2Score++;
            updateScores();
            std::cout << "Player 2 Scored! (" << p2Score << ")\n";
            ResetBall();
        } else if (pos.x > 800) {
            p1Score++;
            updateScores();
            std::cout << "Player 1 Scored! (" << p1Score << ")\n";
            ResetBall();
        }
    }

    void ResetBall() {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_real_distribution<float> yDist(-150.0f, 150.0f);
        static std::uniform_int_distribution<int>    sign(0, 1);

        owner->GetTransform()->SetPosition(400, 300);
        Rigidbody *rb = owner->GetComponent<Rigidbody>();
        if (rb) {
            float dirX = sign(rng) ? 1.0f : -1.0f;
            rb->SetVelocity(dirX * 300.0f, yDist(rng));
        }
    }
};

// ---- main -------------------------------------------------------------
int main() {
    Engine engine;
    if (!engine.Init()) return -1;

    Text::LoadFont("/System/Library/Fonts/SFNSMono.ttf", 52);

    // --- Score displays ---
    auto p1Text = std::make_unique<GameObject>("P1Score");
    p1Text->GetTransform()->SetPosition(200, 40);
    p1Text->AddComponent<Text>("0", 52)->SetColor(100, 180, 255);
    p1ScoreGO = p1Text.get();
    engine.AddGameObject(std::move(p1Text));

    auto p2Text = std::make_unique<GameObject>("P2Score");
    p2Text->GetTransform()->SetPosition(600, 40);
    p2Text->AddComponent<Text>("0", 52)->SetColor(255, 100, 100);
    p2ScoreGO = p2Text.get();
    engine.AddGameObject(std::move(p2Text));

    // --- Walls ---
    auto topWall = std::make_unique<GameObject>("TopWall");
    topWall->GetTransform()->SetPosition(400, -10);
    topWall->AddComponent<Collider>(800, 20, ColliderType::STATIC)->SetBounciness(1.0f);
    engine.AddGameObject(std::move(topWall));

    auto botWall = std::make_unique<GameObject>("BotWall");
    botWall->GetTransform()->SetPosition(400, 610);
    botWall->AddComponent<Collider>(800, 20, ColliderType::STATIC)->SetBounciness(1.0f);
    engine.AddGameObject(std::move(botWall));

    // --- Player 1 paddle (blue) ---
    auto p1 = std::make_unique<GameObject>("Player1");
    p1->GetTransform()->SetPosition(30, 300);
    p1->AddComponent<Sprite>()->SetDimensions(20, 100);
    p1->GetComponent<Sprite>()->SetColor(100, 180, 255);
    p1->AddComponent<PaddleController>(SDLK_w, SDLK_s, 400.0f);
    p1->AddComponent<Collider>(20, 100, ColliderType::DYNAMIC)->SetBounciness(0.0f);
    p1->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
    engine.AddGameObject(std::move(p1));

    // --- Player 2 paddle (red) ---
    auto p2 = std::make_unique<GameObject>("Player2");
    p2->GetTransform()->SetPosition(770, 300);
    p2->AddComponent<Sprite>()->SetDimensions(20, 100);
    p2->GetComponent<Sprite>()->SetColor(255, 100, 100);
    p2->AddComponent<PaddleController>(SDLK_UP, SDLK_DOWN, 400.0f);
    p2->AddComponent<Collider>(20, 100, ColliderType::DYNAMIC)->SetBounciness(0.0f);
    p2->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
    engine.AddGameObject(std::move(p2));

    // --- Ball (white) ---
    auto ball = std::make_unique<GameObject>("Ball");
    ball->GetTransform()->SetPosition(400, 300);
    ball->AddComponent<Sprite>()->SetDimensions(16, 16);
    ball->GetComponent<Sprite>()->SetColor(255, 255, 255);
    ball->AddComponent<Collider>(16, 16, ColliderType::DYNAMIC)->SetBounciness(1.0f);
    auto *rb = ball->AddComponent<Rigidbody>();
    rb->SetGravityScale(0.0f);
    rb->SetVelocity(300, 150);
    rb->SetDrag(0.0f);
    rb->SetMass(1.0f);
    ball->AddComponent<BallLogic>();
    engine.AddGameObject(std::move(ball));

    std::cout << "=== PONG ===\n";
    std::cout << "W/S - Left paddle   |   UP/DOWN - Right paddle\n";
    std::cout << "ESC - quit\n\n";

    engine.Run();
    return 0;
}
