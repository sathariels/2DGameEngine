// OO-vs-ECS benchmark — no SDL, just the architecture question:
//
//   How much does memory layout matter when updating many entities?
//
// Three versions of the same "integrate velocity into position" system:
//
//   1. OO        — heap-allocated entities behind virtual Update(),
//                  like this engine's GameObject/Component model
//   2. AoS       — one contiguous array of fat structs, no virtuals
//   3. SoA/ECS   — parallel arrays holding only the hot data,
//                  like an ECS (EnTT, Unity DOTS, flecs) stores it
//
// The simulation work is identical; only the layout changes.
//
// Build:  cmake --build build --target ecs_benchmark
// Run:    ./build/ecs_benchmark

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <memory>
#include <random>
#include <vector>

namespace {

constexpr int kEntityCount = 200'000;
constexpr int kIterations  = 200;
constexpr float kDt        = 1.0f / 120.0f;

// "Cold" data every game entity drags around (name, health, flags...)
// that the movement system never touches. This is what wrecks cache
// lines in entity-centric layouts.
struct ColdData {
  char name[48] = "entity";
  int  health   = 100;
  int  flags    = 0;
  double spawnTime = 0.0;
};

using Clock = std::chrono::steady_clock;

double MeasureMs(auto &&fn) {
  auto start = Clock::now();
  fn();
  auto end = Clock::now();
  return std::chrono::duration<double, std::milli>(end - start).count();
}

// ---- 1. OO: virtual dispatch, heap-scattered objects ------------------
class Entity {
public:
  virtual ~Entity() = default;
  virtual void Update(float dt) = 0;
  float x = 0, y = 0;

protected:
  ColdData cold;
};

class MovingEntity : public Entity {
public:
  MovingEntity(float vx, float vy) : vx(vx), vy(vy) {}
  void Update(float dt) override {
    x += vx * dt;
    y += vy * dt;
  }

private:
  float vx, vy;
};

// ---- 2. AoS: contiguous array of fat structs ---------------------------
struct EntityAoS {
  float x = 0, y = 0;
  float vx, vy;
  ColdData cold; // still interleaved with the hot data
};

// ---- 3. SoA / ECS-style: hot data in parallel arrays -------------------
struct WorldSoA {
  std::vector<float> x, y, vx, vy;
  std::vector<ColdData> cold; // exists, but lives in its own array
};

} // namespace

int main() {
  std::mt19937 rng{12345};
  std::uniform_real_distribution<float> vel(-100.0f, 100.0f);

  // --- Build the three worlds with identical data ---
  std::vector<float> vxs(kEntityCount), vys(kEntityCount);
  for (int i = 0; i < kEntityCount; ++i) {
    vxs[i] = vel(rng);
    vys[i] = vel(rng);
  }

  // OO world. Allocation order is shuffled so objects are scattered on
  // the heap, the way they end up after a real game has spawned and
  // despawned things for a while.
  std::vector<std::unique_ptr<Entity>> ooWorld(kEntityCount);
  {
    std::vector<int> order(kEntityCount);
    for (int i = 0; i < kEntityCount; ++i) order[i] = i;
    std::shuffle(order.begin(), order.end(), rng);
    for (int i : order)
      ooWorld[i] = std::make_unique<MovingEntity>(vxs[i], vys[i]);
  }

  std::vector<EntityAoS> aosWorld(kEntityCount);
  for (int i = 0; i < kEntityCount; ++i) {
    aosWorld[i].vx = vxs[i];
    aosWorld[i].vy = vys[i];
  }

  WorldSoA soaWorld;
  soaWorld.x.assign(kEntityCount, 0.0f);
  soaWorld.y.assign(kEntityCount, 0.0f);
  soaWorld.vx = vxs;
  soaWorld.vy = vys;
  soaWorld.cold.resize(kEntityCount);

  // --- Run the same system over each layout ---
  double ooMs = MeasureMs([&] {
    for (int it = 0; it < kIterations; ++it)
      for (auto &e : ooWorld)
        e->Update(kDt);
  });

  double aosMs = MeasureMs([&] {
    for (int it = 0; it < kIterations; ++it)
      for (auto &e : aosWorld) {
        e.x += e.vx * kDt;
        e.y += e.vy * kDt;
      }
  });

  double soaMs = MeasureMs([&] {
    for (int it = 0; it < kIterations; ++it)
      for (int i = 0; i < kEntityCount; ++i) {
        soaWorld.x[i] += soaWorld.vx[i] * kDt;
        soaWorld.y[i] += soaWorld.vy[i] * kDt;
      }
  });

  // Checksum so the optimizer can't delete the loops — all three must
  // agree, since they ran the same simulation.
  double check[3] = {0, 0, 0};
  for (int i = 0; i < kEntityCount; ++i) {
    check[0] += ooWorld[i]->x + ooWorld[i]->y;
    check[1] += aosWorld[i].x + aosWorld[i].y;
    check[2] += soaWorld.x[i] + soaWorld.y[i];
  }

  std::printf("Updating %d entities x %d steps:\n\n", kEntityCount,
              kIterations);
  std::printf("  1. OO (virtual, heap-scattered):  %8.2f ms   (1.0x)\n",
              ooMs);
  std::printf("  2. AoS (contiguous fat structs):  %8.2f ms   (%.1fx faster)\n",
              aosMs, ooMs / aosMs);
  std::printf("  3. SoA / ECS (hot data only):     %8.2f ms   (%.1fx faster)\n",
              soaMs, ooMs / soaMs);
  std::printf("\n  checksums: %.1f / %.1f / %.1f %s\n", check[0], check[1],
              check[2],
              (std::abs(check[0] - check[2]) < 1.0 ? "(match)"
                                                   : "(MISMATCH!)"));
  return 0;
}
