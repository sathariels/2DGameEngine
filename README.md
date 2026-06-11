# 2D Game Engine

A lightweight 2D game engine built with C++20 and SDL2, featuring a component-based architecture for flexible game object management. Ships with two complete example games: **Pong** and **Breakout**.

## Features

- **Component-Based Architecture**: Extensible GameObject system with reusable components (Unity-style `AddComponent<T>()` / `GetComponent<T>()`)
- **Fixed-Timestep Physics**: Deterministic simulation at a configurable rate (default 120 Hz) with render interpolation between physics states ("Fix Your Timestep")
- **Spatial-Hash Broadphase**: Collision detection bins colliders into a uniform grid — O(n + pairs) instead of O(n²)
- **Collision System**: AABB detection with static/dynamic/trigger colliders, reflection-with-restitution response, momentum conservation, and enter/stay/exit callbacks
- **Scene Management**: Runtime spawn and deferred destroy (mark-then-sweep at frame boundaries, with automatic physics-pair cleanup), `FindGameObject` by name
- **Dependency Injection**: No global singletons — systems reach components through `UpdateContext`/`RenderContext` passed down from the engine
- **Vector Math**: `Vector2` with dot product, length, normalize, lerp, and reflect
- **Configurable Engine**: Window title/size, target FPS, fixed timestep, quit key, background color, font path, and collider debug drawing via `EngineConfig`
- **Rendering**: Sprites (textured or solid color), procedural textures, and TTF text with per-size font caching and dirty-flag re-rendering
- **Cross-platform**: CMake build with portable SDL2/SDL2_ttf discovery and per-platform default font lookup

## Prerequisites

- C++20 compiler
- CMake 3.16+
- SDL2 and SDL2_ttf development libraries

**macOS (Homebrew):**
```bash
brew install cmake sdl2 sdl2_ttf
```

**Ubuntu/Debian:**
```bash
sudo apt-get install cmake libsdl2-dev libsdl2-ttf-dev
```

**Windows:**
Install SDL2 and SDL2_ttf via [vcpkg](https://vcpkg.io) (`vcpkg install sdl2 sdl2-ttf`) or download from [libsdl.org](https://www.libsdl.org/).

## Building

```bash
cmake -S . -B build
cmake --build build
```

Or just run `./build.sh`. This produces three binaries in `./build`:

| Binary | Description |
|---|---|
| `Pong` | Two-player Pong (W/S vs UP/DOWN) |
| `Breakout` | Breakout with score, lives, win/lose, and runtime brick destroy/respawn |
| `2DGameEngine` | Physics demo — boxes with different bounciness, debug drawing on |
| `ecs_benchmark` | Standalone OO-vs-ECS memory layout benchmark (see [experiments/](experiments/README.md)) |

## Usage Example

```cpp
#include "Engine.h"
#include "Sprite.h"
#include "Rigidbody.h"
#include "Collider.h"

int main() {
    EngineConfig config;
    config.title = "My Game";
    config.windowWidth = 1024;
    config.windowHeight = 768;
    config.debugDrawColliders = false; // set true to see collider outlines

    Engine engine;
    if (!engine.Init(config)) return -1;

    auto player = std::make_unique<GameObject>("Player");
    player->GetTransform()->SetPosition(400, 300); // position = center
    player->AddComponent<Sprite>()->SetDimensions(32, 32);
    player->AddComponent<Collider>(32, 32, ColliderType::DYNAMIC);
    player->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
    engine.AddGameObject(std::move(player));

    engine.Run(); // blocks until quit (ESC or window close by default)
    return 0;
}
```

Custom behavior goes in components — subclass `Component` and override `Update`, `Render`, or the collision callbacks (`OnCollisionEnter` / `Stay` / `Exit`). See [examples/Pong.cpp](examples/Pong.cpp) and [examples/Breakout.cpp](examples/Breakout.cpp).

## Architecture

- **Engine**: Owns all systems and the scene. Fixed-timestep loop: input → N physics steps → game logic → flush spawns/destroys → interpolated render
- **GameObject**: Component container with unique ID, name, and engine backpointer; always has a `Transform`. Destroyed via `engine->Destroy(obj)` (deferred to the frame boundary)
- **Component**: Base class for behaviors. Receives `UpdateContext` (deltaTime, input) and `RenderContext` (renderer, textures, fonts) — no globals
- **Transform**: Position (center-based), rotation, scale; tracks the previous physics position for render interpolation. `SetPosition` is a teleport, `Translate` is continuous motion
- **Physics**: Gravity, semi-implicit Euler integration, spatial-hash broadphase, AABB resolution via reflection-with-restitution, collision pair tracking with enter/stay/exit events
- **Rigidbody**: Velocity, forces, impulses, mass, drag, gravity scale
- **Collider**: AABB bounds with `STATIC` / `DYNAMIC` / `TRIGGER` types and bounciness
- **Sprite / Text**: Rendering components; text caches one texture per (string, size) and re-renders only when dirty
- **InputManager / TextureManager / FontManager**: Keyboard state tracking; texture creation/caching; per-size TTF font caching

### Project Structure

```
include/           # Public headers
src/               # Engine implementation + physics demo entry point
examples/          # Pong and Breakout
experiments/       # ECS layout benchmark + writeup
CMakeLists.txt     # Builds engine library + all executables
```

## Roadmap

- [ ] Image file texture loading (SDL2_image)
- [ ] Audio system integration
- [ ] Animation system
- [ ] Tilemap support
- [ ] Frame-time profiler overlay

## License

This project is for educational purposes. SDL2 is licensed under the zlib license.
