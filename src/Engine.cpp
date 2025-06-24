#include "Engine.h"
#include <iostream>
#include <thread>
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"

Engine::Engine() : window(nullptr), isRunning(false) {}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "2D Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;

    // Create some test game objects
    CreateTestObjects();

    return true;
}

void Engine::CreateTestObjects() {
    // Create a player object
    auto player = std::make_unique<GameObject>("Player");
    player->GetTransform()->SetPosition(400, 300);
    gameObjects.push_back(std::move(player));

    // Create an enemy object
    auto enemy = std::make_unique<GameObject>("Enemy");
    enemy->GetTransform()->SetPosition(200, 150);
    enemy->GetTransform()->SetScale(1.5f); // Make it bigger
    gameObjects.push_back(std::move(enemy));

    // Create a moving object
    auto movingBox = std::make_unique<GameObject>("MovingBox");
    movingBox->GetTransform()->SetPosition(600, 400);
    gameObjects.push_back(std::move(movingBox));

    std::cout << "Created " << gameObjects.size() << " game objects" << std::endl;
}

void Engine::Run() {
    using clock = std::chrono::high_resolution_clock;
    const std::chrono::milliseconds frameDuration(1000 / targetFPS);

    while (isRunning) {
        auto frameStart = clock::now();

        HandleEvents();
        Update(frameDuration.count() / 1000.0f);
        Render();

        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}

void Engine::HandleEvents() {
    input.Update();

    if (input.IsKeyPressed(SDLK_ESCAPE)) {
        isRunning = false;
    }

    // Test input with game objects
    if (!gameObjects.empty()) {
        Transform* playerTransform = gameObjects[0]->GetTransform();

        float moveSpeed = 200.0f; // pixels per second
        Vector2 movement(0, 0);

        if (input.IsKeyHeld(SDLK_w) || input.IsKeyHeld(SDLK_UP)) {
            movement.y = -moveSpeed;
        }
        if (input.IsKeyHeld(SDLK_s) || input.IsKeyHeld(SDLK_DOWN)) {
            movement.y = moveSpeed;
        }
        if (input.IsKeyHeld(SDLK_a) || input.IsKeyHeld(SDLK_LEFT)) {
            movement.x = -moveSpeed;
        }
        if (input.IsKeyHeld(SDLK_d) || input.IsKeyHeld(SDLK_RIGHT)) {
            movement.x = moveSpeed;
        }

        // Apply movement (will be multiplied by deltaTime in Update)
        if (movement.x != 0 || movement.y != 0) {
            // We'll store this for the update phase
            static Vector2 pendingMovement;
            pendingMovement = movement;
        }
    }
}

void Engine::Update(float deltaTime) {
    // Update all game objects
    for (auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }

    // Example: Move the first object (player) with input
    if (!gameObjects.empty()) {
        Transform* playerTransform = gameObjects[0]->GetTransform();

        float moveSpeed = 200.0f; // pixels per second
        Vector2 movement(0, 0);

        if (input.IsKeyHeld(SDLK_w) || input.IsKeyHeld(SDLK_UP)) {
            movement.y = -moveSpeed * deltaTime;
        }
        if (input.IsKeyHeld(SDLK_s) || input.IsKeyHeld(SDLK_DOWN)) {
            movement.y = moveSpeed * deltaTime;
        }
        if (input.IsKeyHeld(SDLK_a) || input.IsKeyHeld(SDLK_LEFT)) {
            movement.x = -moveSpeed * deltaTime;
        }
        if (input.IsKeyHeld(SDLK_d) || input.IsKeyHeld(SDLK_RIGHT)) {
            movement.x = moveSpeed * deltaTime;
        }

        playerTransform->Translate(movement);
    }

    // Example: Rotate the second object
    if (gameObjects.size() > 1) {
        gameObjects[1]->GetTransform()->Rotate(90.0f * deltaTime); // 90 degrees per second
    }

    // Example: Move the third object in a circle
    if (gameObjects.size() > 2) {
        static float time = 0.0f;
        time += deltaTime;

        float radius = 100.0f;
        float centerX = 600.0f;
        float centerY = 400.0f;

        float x = centerX + radius * cos(time);
        float y = centerY + radius * sin(time);

        gameObjects[2]->GetTransform()->SetPosition(x, y);
    }
}

void Engine::Render() {
    // Set background color
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    // Render all game objects
    for (auto& gameObject : gameObjects) {
        if (gameObject->IsActive()) {
            // For now, we'll render each GameObject as a colored rectangle
            // Later, this will be handled by Sprite components
            RenderGameObject(gameObject.get());
        }
    }

    SDL_RenderPresent(renderer);
}

void Engine::RenderGameObject(GameObject* gameObject) {
    Transform* transform = gameObject->GetTransform();

    // Choose color based on object name
    if (gameObject->GetName() == "Player") {
        SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255); // Green
    } else if (gameObject->GetName() == "Enemy") {
        SDL_SetRenderDrawColor(renderer, 150, 50, 50, 255); // Red
    } else {
        SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255); // Blue
    }

    // Get rectangle from transform (using 50x50 as default size)
    SDL_Rect rect = transform->ToSDLRect(50, 50);
    SDL_RenderFillRect(renderer, &rect);

    // Optional: Draw a border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White border
    SDL_RenderDrawRect(renderer, &rect);
}

void Engine::Shutdown() {
    // Clear game objects before shutting down SDL
    gameObjects.clear();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}