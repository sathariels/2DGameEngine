#include "Engine.h"
#include <iostream>
#include <thread>
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Rigidbody.h"
#include "Collider.h"

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

    // Initialize physics system
    physics = std::make_unique<Physics>();

    // Set static references for Sprite class
    Sprite::SetRenderer(renderer);
    Sprite::SetTextureManager(textureManager.get());

    // Set static references for Collider debug drawing
    Collider::SetDebugRenderer(renderer);
    Collider::SetGlobalDebugDraw(true); // Enable debug visualization

    isRunning = true;

    // Create physics demo objects
    CreatePhysicsDemo();

    return true;
}

void Engine::CreatePhysicsDemo() {
    // Create ground (static platform)
    auto ground = std::make_unique<GameObject>("Ground");
    ground->GetTransform()->SetPosition(400, 550);

    auto groundSprite = ground->AddComponent<Sprite>();
    SDL_Texture* groundTexture = textureManager->CreateColorTexture(600, 50, 100, 100, 100, 255);
    groundSprite->SetTexture(groundTexture);

    auto groundCollider = ground->AddComponent<Collider>(600, 50, ColliderType::STATIC);
    groundCollider->SetBounciness(0.3f);

    gameObjects.push_back(std::move(ground));

    // Create bouncing ball
    auto ball = std::make_unique<GameObject>("Ball");
    ball->GetTransform()->SetPosition(200, 100);

    auto ballSprite = ball->AddComponent<Sprite>();
    SDL_Texture* ballTexture = textureManager->CreateGradientTexture(40, 40, 255, 100, 100, 150, 50, 50);
    ballSprite->SetTexture(ballTexture);

    auto ballRigidbody = ball->AddComponent<Rigidbody>();
    ballRigidbody->SetVelocity(150, 0); // Start with horizontal velocity

    auto ballCollider = ball->AddComponent<Collider>(40, 40, ColliderType::DYNAMIC);
    ballCollider->SetBounciness(0.8f);

    gameObjects.push_back(std::move(ball));

    // Create controllable player
    auto player = std::make_unique<GameObject>("Player");
    player->GetTransform()->SetPosition(400, 300);

    auto playerSprite = player->AddComponent<Sprite>();
    SDL_Texture* playerTexture = textureManager->CreateCheckeredTexture(50, 50, 100, 255, 100, 50, 150, 50);
    playerSprite->SetTexture(playerTexture);

    auto playerRigidbody = player->AddComponent<Rigidbody>();
    playerRigidbody->SetGravityScale(0.0f); // Player not affected by gravity
    playerRigidbody->SetDrag(5.0f); // High drag for responsive controls

    auto playerCollider = player->AddComponent<Collider>(50, 50, ColliderType::DYNAMIC);
    playerCollider->SetBounciness(0.1f);

    gameObjects.push_back(std::move(player));

    // Create left wall
    auto leftWall = std::make_unique<GameObject>("LeftWall");
    leftWall->GetTransform()->SetPosition(25, 300);

    auto leftWallSprite = leftWall->AddComponent<Sprite>();
    SDL_Texture* wallTexture = textureManager->CreateColorTexture(50, 600, 80, 80, 80, 255);
    leftWallSprite->SetTexture(wallTexture);

    auto leftWallCollider = leftWall->AddComponent<Collider>(50, 600, ColliderType::STATIC);
    leftWallCollider->SetBounciness(0.5f);

    gameObjects.push_back(std::move(leftWall));

    // Create right wall
    auto rightWall = std::make_unique<GameObject>("RightWall");
    rightWall->GetTransform()->SetPosition(775, 300);

    auto rightWallSprite = rightWall->AddComponent<Sprite>();
    rightWallSprite->SetTexture(wallTexture); // Reuse wall texture

    auto rightWallCollider = rightWall->AddComponent<Collider>(50, 600, ColliderType::STATIC);
    rightWallCollider->SetBounciness(0.5f);

    gameObjects.push_back(std::move(rightWall));

    std::cout << "Created physics demo with " << gameObjects.size() << " objects" << std::endl;
    std::cout << "Controls: WASD to move player, SPACE to add force to player, R to reset ball" << std::endl;
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
    // Update physics system
    physics->Update(deltaTime, gameObjects);

    // Update all game objects
    for (auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }

    // Handle player input
    if (!gameObjects.empty()) {
        // Find player object
        GameObject* player = nullptr;
        for (auto& obj : gameObjects) {
            if (obj->GetName() == "Player") {
                player = obj.get();
                break;
            }
        }

        if (player) {
            Rigidbody* playerRigidbody = player->GetComponent<Rigidbody>();

            if (playerRigidbody) {
                float moveForce = 1000.0f; // Force applied per second

                // Apply forces based on input
                if (input.IsKeyHeld(SDLK_w) || input.IsKeyHeld(SDLK_UP)) {
                    playerRigidbody->AddForce(0, -moveForce * deltaTime);
                }
                if (input.IsKeyHeld(SDLK_s) || input.IsKeyHeld(SDLK_DOWN)) {
                    playerRigidbody->AddForce(0, moveForce * deltaTime);
                }
                if (input.IsKeyHeld(SDLK_a) || input.IsKeyHeld(SDLK_LEFT)) {
                    playerRigidbody->AddForce(-moveForce * deltaTime, 0);
                }
                if (input.IsKeyHeld(SDLK_d) || input.IsKeyHeld(SDLK_RIGHT)) {
                    playerRigidbody->AddForce(moveForce * deltaTime, 0);
                }

                // Space for upward impulse
                if (input.IsKeyPressed(SDLK_SPACE)) {
                    playerRigidbody->AddImpulse(Vector2(0, -300));
                }
            }
        }

        // R to reset ball position
        if (input.IsKeyPressed(SDLK_r)) {
            for (auto& obj : gameObjects) {
                if (obj->GetName() == "Ball") {
                    obj->GetTransform()->SetPosition(200, 100);
                    auto rigidbody = obj->GetComponent<Rigidbody>();
                    if (rigidbody) {
                        rigidbody->SetVelocity(150, 0);
                    }
                    break;
                }
            }
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

    // Clean up systems
    physics.reset();
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