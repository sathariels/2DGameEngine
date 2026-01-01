#include "../include/Engine.h"

int main() {
    Engine engine;

    if (engine.Init()) {
        engine.Run();
    }

    engine.Shutdown();
    return 0;
}
