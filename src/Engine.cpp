#include "Engine.h"
#include <iostream>
#include <thread>
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"

Engine::Engine() : window(nullptr), renderer(nullptr), isRunning(false) {}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "2D Game Engine with Sprites",
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

    // Initialize texture manager
    textureManager = std::make_unique<TextureManager>(renderer);

    // Set static references for Sprite class
    Sprite::SetRenderer(renderer);
    Sprite::SetTextureManager(textureManager.get());

    isRunning = true;

    // Create test objects with sprites
    CreateTestSprites();

    return true;
}

void Engine::CreateTestSprites() {
    // Create a player with a gradient texture
    auto player = std::make_unique<GameObject>("Player");
    player->GetTransform()->SetPosition(400, 300);

    auto playerSprite = player->AddComponent<Sprite>();
    SDL_Texture* playerTexture = textureManager->CreateGradientTexture(64, 64, 100, 255, 100, 50, 150, 50);
    playerSprite->SetTexture(playerTexture);

    gameObjects.push_back(std::move(player));

    // Create an enemy with a checkered texture
    auto enemy = std::make_unique<GameObject>("Enemy");
    enemy->GetTransform()->SetPosition(200, 150);
    enemy->GetTransform()->SetScale(1.2f);

    auto enemySprite = enemy->AddComponent<Sprite>();
    SDL_Texture* enemyTexture = textureManager->CreateCheckeredTexture(48, 48, 255, 100, 100, 150, 50, 50);
    enemySprite->SetTexture(enemyTexture);

    gameObjects.push_back(std::move(enemy));

    // Create a moving object with solid blue
    auto movingBox = std::make_unique<GameObject>("MovingBox");
    movingBox->GetTransform()->SetPosition(600, 400);

    auto movingSprite = movingBox->AddComponent<Sprite>();
    SDL_Texture* blueTexture = textureManager->CreateColorTexture(40, 40, 100, 150, 255, 255);
    movingSprite->SetTexture(blueTexture);

    gameObjects.push_back(std::move(movingBox));

    // Create a semi-transparent gradient object
    auto ghostBox = std::make_unique<GameObject>("Ghost");
    ghostBox->GetTransform()->SetPosition(100, 400);

    auto ghostSprite = ghostBox->AddComponent<Sprite>();
    SDL_Texture* ghostTexture = textureManager->CreateGradientTexture(60, 60, 255, 200, 255, 100, 50, 150);
    ghostSprite->SetTexture(ghostTexture);
    ghostSprite->SetAlpha(128); // Make it semi-transparent

    gameObjects.push_back(std::move(ghostBox));

    std::cout << "Created " << gameObjects.size() << " game objects with sprites" << std::endl;
}

void Engine::CreateTestObjects() {
    // This method is now replaced by CreateTestSprites()
    // Kept for backward compatibility
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

        // Test sprite color changes
        if (input.IsKeyPressed(SDLK_SPACE)) {
            auto sprite = gameObjects[0]->GetComponent<Sprite>();
            if (sprite) {
                // Toggle between normal and red tint
                static bool isRed = false;
                if (isRed) {
                    sprite->SetColor(255, 255, 255, 255); // Normal
                } else {
                    sprite->SetColor(255, 100, 100, 255); // Red tint
                }
                isRed = !isRed;
            }
        }
    }

    // Example: Rotate the second object
    if (gameObjects.size() > 1) {
        gameObjects[1]->GetTransform()->Rotate(90.0f * deltaTime);
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

    // Example: Fade the ghost object in and out
    if (gameObjects.size() > 3) {
        static float ghostTime = 0.0f;
        ghostTime += deltaTime;

        auto ghostSprite = gameObjects[3]->GetComponent<Sprite>();
        if (ghostSprite) {
            Uint8 alpha = static_cast<Uint8>(127 + 127 * sin(ghostTime * 2.0f));
            ghostSprite->SetAlpha(alpha);
        }
    }
}

void Engine::Render() {
    // Set background color
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    // Render all game objects (they now use their Sprite components)
    for (auto& gameObject : gameObjects) {
        if (gameObject->IsActive()) {
            gameObject->Render(); // This will call Sprite::Render() for each object
        }
    }

    SDL_RenderPresent(renderer);
}

void Engine::RenderGameObject(GameObject* gameObject) {
    // This method is no longer needed since GameObjects render themselves
    // via their Sprite components, but keeping for backward compatibility

    // If a GameObject doesn't have a Sprite component, render as colored rectangle
    if (!gameObject->GetComponent<Sprite>()) {
        Transform* transform = gameObject->GetTransform();

        // Choose color based on object name
        if (gameObject->GetName() == "Player") {
            SDL_SetRenderDrawColor(renderer, 50, 150, 50, 255);
        } else if (gameObject->GetName() == "Enemy") {
            SDL_SetRenderDrawColor(renderer, 150, 50, 50, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
        }

        SDL_Rect rect = transform->ToSDLRect(50, 50);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Engine::Shutdown() {
    // Clear game objects before shutting down
    gameObjects.clear();

    // Clean up texture manager
    textureManager.reset();

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