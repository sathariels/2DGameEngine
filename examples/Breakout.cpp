#include "Collider.h"
#include "Component.h"
#include "Engine.h"
#include "InputManager.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "Text.h"
#include "Transform.h"
#include "UpdateContext.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

// All SetPosition calls use CENTER (engine convention).

// ---- Game state -------------------------------------------------------
static int  score      = 0;
static int  lives      = 3;
static bool ballInPlay = false;
static GameObject *scoreTextGO = nullptr;
static GameObject *livesTextGO = nullptr;

static constexpr int BRICK_W    = 90;
static constexpr int BRICK_H    = 22;
static constexpr int BRICK_GAP  = 5;
static constexpr int BRICK_COLS = 8;
static constexpr int BRICK_ROWS = 6;

// One color per row (R, G, B)
static constexpr SDL_Color ROW_COLORS[BRICK_ROWS] = {
    {220,  60,  60, 255}, // row 0 — red
    {220, 140,  50, 255}, // row 1 — orange
    {220, 220,  50, 255}, // row 2 — yellow
    { 60, 200,  80, 255}, // row 3 — green
    { 60, 180, 220, 255}, // row 4 — cyan
    {160,  80, 220, 255}, // row 5 — purple
};

static void updateHUD() {
    if (scoreTextGO)
        scoreTextGO->GetComponent<Text>()->SetText("Score: " + std::to_string(score));
    if (livesTextGO)
        livesTextGO->GetComponent<Text>()->SetText("Lives: " + std::to_string(lives));
}

// ---- Brick component --------------------------------------------------
class Brick : public Component {
public:
    void OnCollisionEnter(GameObject *other) override;
};

// Spawns a fresh grid of bricks. Safe to call mid-game: new objects
// enter the scene at the next frame boundary (deferred add).
static void spawnBricks(Engine &engine) {
    const float gridLeft =
        (engine.GetWindowWidth() -
         (BRICK_COLS * BRICK_W + (BRICK_COLS - 1) * BRICK_GAP)) / 2.0f;
    const float gridTop = 70.0f;

    for (int row = 0; row < BRICK_ROWS; ++row) {
        SDL_Color c = ROW_COLORS[row];
        for (int col = 0; col < BRICK_COLS; ++col) {
            float cx = gridLeft + BRICK_W / 2.0f + col * (BRICK_W + BRICK_GAP);
            float cy = gridTop  + BRICK_H / 2.0f + row * (BRICK_H + BRICK_GAP);

            auto brick = std::make_unique<GameObject>(
                "Brick_" + std::to_string(row) + "_" + std::to_string(col));
            brick->GetTransform()->SetPosition(cx, cy);
            brick->AddComponent<Sprite>()->SetDimensions(BRICK_W, BRICK_H);
            brick->GetComponent<Sprite>()->SetColor(c.r, c.g, c.b);
            brick->AddComponent<Collider>(BRICK_W, BRICK_H, ColliderType::TRIGGER);
            brick->AddComponent<Brick>();
            engine.AddGameObject(std::move(brick));
        }
    }
}

// Destroys every brick still in the scene (used on game over)
static void destroyRemainingBricks(Engine &engine) {
    for (auto &obj : engine.GetGameObjects()) {
        if (obj->HasComponent<Brick>()) {
            engine.Destroy(obj.get());
        }
    }
}

static int countRemainingBricks(Engine &engine) {
    int count = 0;
    for (auto &obj : engine.GetGameObjects()) {
        if (obj->IsActive() && obj->HasComponent<Brick>()) ++count;
    }
    return count;
}

// ---- Paddle -----------------------------------------------------------
class BreakoutPaddle : public Component {
public:
    explicit BreakoutPaddle(float speed) : speed(speed) {}

    void Update(const UpdateContext &ctx) override {
        if (!ctx.input) return;

        Rigidbody *rb = owner->GetComponent<Rigidbody>();
        if (!rb) return;

        rb->SetVelocity(0, 0);
        if (ctx.input->IsKeyHeld(SDLK_LEFT) || ctx.input->IsKeyHeld(SDLK_a))
            rb->SetVelocity(-speed, 0);
        else if (ctx.input->IsKeyHeld(SDLK_RIGHT) || ctx.input->IsKeyHeld(SDLK_d))
            rb->SetVelocity(speed, 0);

        // Clamp center so edges stay on screen (half-width = 45)
        Transform *t = owner->GetTransform();
        Vector2    p = t->GetPosition();
        float maxX = owner->GetEngine()->GetWindowWidth() - 45.0f;
        if (p.x < 45.0f)      t->SetPosition(45.0f, p.y);
        else if (p.x > maxX)  t->SetPosition(maxX, p.y);
    }

private:
    float speed;
};

// ---- Ball -------------------------------------------------------------
class BreakoutBall : public Component {
public:
    void Update(const UpdateContext &ctx) override {
        Vector2 pos = owner->GetTransform()->GetPosition();

        if (pos.y > owner->GetEngine()->GetWindowHeight() + 20) {
            --lives;
            if (lives <= 0) {
                std::cout << "GAME OVER! Final Score: " << score << "\n";
                score = 0;
                lives = 3;
                Engine *engine = owner->GetEngine();
                destroyRemainingBricks(*engine);
                spawnBricks(*engine);
            }
            updateHUD();
            reset();
        }
    }

    // Called by Brick::OnCollisionEnter to bounce the ball off it
    void bounceOff(GameObject *brick) {
        Rigidbody *rb      = owner->GetComponent<Rigidbody>();
        Collider  *ballCol = owner->GetComponent<Collider>();
        Collider  *brickCol = brick->GetComponent<Collider>();
        if (!rb || !ballCol || !brickCol) return;

        SDL_Rect br  = brickCol->GetBounds();
        SDL_Rect bal = ballCol->GetBounds();

        float ox = std::min(bal.x + bal.w, br.x + br.w) - std::max(bal.x, br.x);
        float oy = std::min(bal.y + bal.h, br.y + br.h) - std::max(bal.y, br.y);

        Vector2 vel = rb->GetVelocity();
        if (ox < oy) rb->SetVelocity(-vel.x,  vel.y);
        else          rb->SetVelocity( vel.x, -vel.y);
    }

    void launch() {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_real_distribution<float> xDist(130.0f, 230.0f);
        static std::uniform_int_distribution<int>    signDist(0, 1);

        Rigidbody *rb = owner->GetComponent<Rigidbody>();
        if (!rb) return;
        float vx = xDist(rng) * (signDist(rng) ? 1.0f : -1.0f);
        rb->SetVelocity(vx, -420.0f);
        ballInPlay = true;
    }

    void reset() {
        ballInPlay = false;
        owner->GetTransform()->SetPosition(400, 510);
        Rigidbody *rb = owner->GetComponent<Rigidbody>();
        if (rb) rb->SetVelocity(0, 0);
        std::cout << "Press SPACE to launch.\n";
    }
};

// ---- Brick::OnCollisionEnter implementation (needs BreakoutBall defined) ----
void Brick::OnCollisionEnter(GameObject *other) {
    BreakoutBall *ball = other->GetComponent<BreakoutBall>();
    if (!ball) return;

    ball->bounceOff(owner); // bounce before the brick goes away
    score += 10;
    updateHUD();

    // Deferred destruction: the brick leaves the scene at the next frame
    // boundary, and its physics pairs are purged automatically.
    owner->GetEngine()->Destroy(owner);
}

// ---- Ball Launcher ----------------------------------------------------
class BallLauncher : public Component {
public:
    void Update(const UpdateContext &ctx) override {
        if (ballInPlay || !ctx.input) return;
        if (ctx.input->IsKeyPressed(SDLK_SPACE)) {
            BreakoutBall *ball = owner->GetComponent<BreakoutBall>();
            if (ball) ball->launch();
        }
    }
};

// ---- Win checker (runs on its own GameObject so it's always active) ---
class WinChecker : public Component {
public:
    void Update(const UpdateContext &ctx) override {
        if (!ballInPlay) return;

        Engine *engine = owner->GetEngine();
        if (countRemainingBricks(*engine) > 0) return;

        std::cout << "YOU WIN! Score: " << score << "\n";
        spawnBricks(*engine);

        if (ballGO) {
            BreakoutBall *ball = ballGO->GetComponent<BreakoutBall>();
            if (ball) ball->reset();
            updateHUD();
        }
    }
    GameObject *ballGO = nullptr;
};

// ---- main -------------------------------------------------------------
int main() {
    EngineConfig config;
    config.title = "Breakout";

    Engine engine;
    if (!engine.Init(config)) return -1;

    // --- HUD ---
    auto scoreTxt = std::make_unique<GameObject>("ScoreText");
    scoreTxt->GetTransform()->SetPosition(120, 20);
    scoreTxt->AddComponent<Text>("Score: 0", 22)->SetColor(255, 255, 255);
    scoreTextGO = engine.AddGameObject(std::move(scoreTxt));

    auto livesTxt = std::make_unique<GameObject>("LivesText");
    livesTxt->GetTransform()->SetPosition(670, 20);
    livesTxt->AddComponent<Text>("Lives: 3", 22)->SetColor(255, 220, 100);
    livesTextGO = engine.AddGameObject(std::move(livesTxt));

    // --- Walls ---
    auto topWall = std::make_unique<GameObject>("TopWall");
    topWall->GetTransform()->SetPosition(400, -10);
    topWall->AddComponent<Collider>(800, 20, ColliderType::STATIC)->SetBounciness(1.0f);
    engine.AddGameObject(std::move(topWall));

    auto leftWall = std::make_unique<GameObject>("LeftWall");
    leftWall->GetTransform()->SetPosition(-10, 300);
    leftWall->AddComponent<Collider>(20, 600, ColliderType::STATIC)->SetBounciness(1.0f);
    engine.AddGameObject(std::move(leftWall));

    auto rightWall = std::make_unique<GameObject>("RightWall");
    rightWall->GetTransform()->SetPosition(810, 300);
    rightWall->AddComponent<Collider>(20, 600, ColliderType::STATIC)->SetBounciness(1.0f);
    engine.AddGameObject(std::move(rightWall));

    // --- Bricks (TRIGGER — physics notifies but doesn't resolve) ---
    spawnBricks(engine);

    // --- Paddle ---
    auto paddle = std::make_unique<GameObject>("Paddle");
    paddle->GetTransform()->SetPosition(400, 555);
    paddle->AddComponent<Sprite>()->SetDimensions(90, 14);
    paddle->GetComponent<Sprite>()->SetColor(100, 200, 255);
    paddle->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
    paddle->AddComponent<Collider>(90, 14, ColliderType::STATIC)->SetBounciness(1.0f);
    paddle->AddComponent<BreakoutPaddle>(500.0f);
    engine.AddGameObject(std::move(paddle));

    // --- Ball ---
    auto ball = std::make_unique<GameObject>("Ball");
    ball->GetTransform()->SetPosition(400, 510);
    ball->AddComponent<Sprite>()->SetDimensions(12, 12);
    ball->GetComponent<Sprite>()->SetColor(255, 255, 255);
    auto *rb = ball->AddComponent<Rigidbody>();
    rb->SetGravityScale(0.0f);
    rb->SetDrag(0.0f);
    rb->SetMass(1.0f);
    ball->AddComponent<Collider>(12, 12, ColliderType::DYNAMIC)->SetBounciness(1.0f);
    ball->AddComponent<BreakoutBall>();
    ball->AddComponent<BallLauncher>();
    GameObject *ballPtr = engine.AddGameObject(std::move(ball));

    // --- Win checker ---
    auto checker = std::make_unique<GameObject>("WinChecker");
    auto *wc = checker->AddComponent<WinChecker>();
    wc->ballGO = ballPtr;
    engine.AddGameObject(std::move(checker));

    std::cout << "=== BREAKOUT ===\n";
    std::cout << "LEFT / RIGHT  (or A / D) - move paddle\n";
    std::cout << "SPACE         - launch ball\n";
    std::cout << "ESC           - quit\n\n";
    std::cout << "Press SPACE to launch.\n";

    engine.Run();
    return 0;
}
