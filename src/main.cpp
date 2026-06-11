#include "../include/Collider.h"
#include "../include/Engine.h"
#include "../include/Rigidbody.h"
#include "../include/Sprite.h"
#include "../include/Transform.h"

// Bare engine demo: boxes with different bounciness falling onto a
// floor. Shows gravity, restitution, and fixed-timestep interpolation.
int main() {
    EngineConfig config;
    config.title = "2D Game Engine — physics demo";
    config.debugDrawColliders = true;

    Engine engine;
    if (!engine.Init(config)) return -1;

    auto floor = std::make_unique<GameObject>("Floor");
    floor->GetTransform()->SetPosition(400, 580);
    floor->AddComponent<Sprite>()->SetDimensions(800, 40);
    floor->GetComponent<Sprite>()->SetColor(80, 80, 100);
    floor->AddComponent<Collider>(800, 40, ColliderType::STATIC);
    engine.AddGameObject(std::move(floor));

    const float bounciness[] = {0.0f, 0.4f, 0.7f, 0.9f};
    for (int i = 0; i < 4; ++i) {
        auto box = std::make_unique<GameObject>("Box" + std::to_string(i));
        box->GetTransform()->SetPosition(160.0f + i * 160.0f, 100);
        box->AddComponent<Sprite>()->SetDimensions(40, 40);
        box->GetComponent<Sprite>()->SetColor(100 + i * 40, 180, 255 - i * 40);
        box->AddComponent<Collider>(40, 40, ColliderType::DYNAMIC)
            ->SetBounciness(bounciness[i]);
        box->AddComponent<Rigidbody>()->SetDrag(0.0f);
        engine.AddGameObject(std::move(box));
    }

    engine.Run();
    return 0;
}
