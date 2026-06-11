# Experiments

## `ecs_benchmark` — component objects vs. data-oriented ECS

This engine uses a **component-object model**: each `GameObject` owns a
map of heap-allocated `Component`s, and systems reach behavior through
virtual calls. It's the same shape as classic Unity
(`GameObject`/`MonoBehaviour`) — easy to write, easy to extend, and the
right call for a small game.

The other school is the **Entity Component System (ECS)**: entities are
just IDs, components are plain data packed into contiguous arrays, and
systems are loops over those arrays. That's how EnTT, flecs, and Unity
DOTS work.

The benchmark runs the *same* movement system over three layouts:

| Layout | What it models |
|---|---|
| OO (virtual + heap-scattered) | This engine / classic Unity |
| AoS (array of fat structs) | "Just put them in a vector" |
| SoA (parallel hot-data arrays) | ECS-style storage |

Build and run:

```bash
cmake --build build --target ecs_benchmark
./build/ecs_benchmark
```

### Why the ECS layout wins on throughput

It isn't about virtual-call overhead — that's small. It's **cache
locality**:

- The CPU loads memory in 64-byte cache lines. In the OO version, each
  entity is somewhere else on the heap, and most of each fetched line is
  cold data (name, health, flags) the movement system never reads.
- In the SoA version, every byte the loop touches is data it needs, in
  the order it needs it. The hardware prefetcher sees a linear scan and
  stays ahead of you. The same property is what makes the loop trivially
  vectorizable (SIMD) and parallelizable.

### Why this engine still uses component objects

- At hundreds of objects (Pong, Breakout), the difference is noise; the
  ergonomic cost of ECS is not.
- Gameplay logic is branchy and entity-centric — it reads *many*
  components of *one* entity, which is the access pattern OO is good at.
  ECS shines when systems read *one* component of *many* entities.
- The debate is a tradeoff, not a verdict: engines increasingly mix both
  (Unity keeps GameObjects alongside DOTS; Unreal added Mass on top of
  Actors).

The honest summary for an interview: *"Component objects optimize for
programmer iteration; ECS optimizes for memory bandwidth. I'd start with
objects and move hot systems (particles, projectiles, crowds) to ECS
storage when profiling says so."*

To go deeper, read the [EnTT](https://github.com/skypjack/entt) docs
(the `entt::registry` API) and Mike Acton's "Data-Oriented Design and
C++" talk (CppCon 2014).
