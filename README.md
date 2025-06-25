# 2D Game Engine

A lightweight 2D game engine built with C++ and SDL2, featuring a component-based architecture for flexible game object management.

## Features

- **Component-Based Architecture**: Extensible GameObject system with reusable components
- **Input Management**: Comprehensive keyboard input handling with press/hold/release detection
- **Transform System**: Position, rotation, and scale management for all game objects
- **Real-time Rendering**: 60 FPS game loop with SDL2 rendering
- **Cross-platform**: Built with CMake for easy compilation on multiple platforms

## Demo

The current build includes three interactive objects:
- **Green Rectangle (Player)**: Move with WASD or arrow keys
- **Red Rectangle (Enemy)**: Automatically rotates
- **Blue Rectangle**: Moves in a circular pattern

## Prerequisites

- C++20 compiler
- SDL2 development libraries
- CMake 3.29 or higher

### Installing SDL2

**macOS (Homebrew):**
```bash
brew install sdl2
```

**Ubuntu/Debian:**
```bash
sudo apt-get install libsdl2-dev
```

**Windows:**
Download SDL2 development libraries from [libsdl.org](https://www.libsdl.org/download-2.0.php)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./2DGameEngine
```

## Controls

- **WASD** or **Arrow Keys**: Move player (green rectangle)
- **ESC**: Exit game

## Architecture

### Core Classes

- **Engine**: Main game loop, rendering, and system coordination
- **GameObject**: Container for components with unique ID and name
- **Component**: Base class for all game object behaviors
- **Transform**: Position, rotation, and scale component (automatically added to all GameObjects)
- **InputManager**: Handles keyboard input with state tracking

### Project Structure

```
src/
├── Engine.cpp/h          # Main engine and game loop
├── GameObject.cpp/h      # Component-based game object system
├── Component.cpp/h       # Base component class
├── Transform.cpp/h       # Position/rotation/scale component
├── InputManager.cpp/h    # Input handling system
└── main.cpp             # Entry point

CMakeLists.txt           # Build configuration
```

## Usage Example

```cpp
// Create a new game object
auto player = std::make_unique<GameObject>("Player");

// Position it in the world
player->GetTransform()->SetPosition(400, 300);

// Add to the game world
gameObjects.push_back(std::move(player));

// Add custom components (when implemented)
// player->AddComponent<Sprite>("player.png");
// player->AddComponent<Rigidbody>();
```

## Roadmap

### Immediate Goals
- [ ] Sprite rendering system with texture loading
- [ ] Basic 2D physics and collision detection
- [ ] Audio system integration
- [ ] Scene management

### Future Features
- [ ] Animation system
- [ ] Particle effects
- [ ] Tilemap support
- [ ] Entity serialization
- [ ] Scripting support

## Contributing

This is a learning project focused on understanding game engine architecture. Feel free to explore the code and suggest improvements!

## Dependencies

- **SDL2**: Graphics, window management, and input
- **Standard C++ Library**: Core functionality

## License

This project is for educational purposes. SDL2 is licensed under the zlib license.
