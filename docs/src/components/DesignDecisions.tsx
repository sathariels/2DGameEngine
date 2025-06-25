
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';

const DesignDecisions = () => {
  return (
    <section className="py-20 bg-background">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12 animate-fade-in-up">
          <h2 className="text-4xl font-bold mb-4 text-gradient">Design Decisions</h2>
          <p className="text-xl text-muted-foreground max-w-3xl mx-auto">
            Key architectural choices that shaped the engine's performance, 
            maintainability, and extensibility.
          </p>
        </div>
        
        <div className="max-w-6xl mx-auto animate-fade-in">
          <Tabs defaultValue="ecs" className="space-y-8">
            <TabsList className="grid w-full grid-cols-2 lg:grid-cols-4 h-auto p-1">
              <TabsTrigger value="ecs" className="text-sm py-3">ECS Architecture</TabsTrigger>
              <TabsTrigger value="rendering" className="text-sm py-3">Rendering Pipeline</TabsTrigger>
              <TabsTrigger value="memory" className="text-sm py-3">Memory Management</TabsTrigger>
              <TabsTrigger value="scripting" className="text-sm py-3">Scripting System</TabsTrigger>
            </TabsList>
            
            <TabsContent value="ecs" className="space-y-6">
              <Card className="border-l-4 border-l-engine-blue">
                <CardHeader>
                  <CardTitle className="text-2xl">Entity-Component-System Pattern</CardTitle>
                </CardHeader>
                <CardContent className="space-y-4">
                  <p className="text-muted-foreground leading-relaxed">
                    Chose ECS over traditional object-oriented hierarchy to achieve better cache locality, 
                    easier parallelization, and more flexible entity composition.
                  </p>
                  
                  <div className="bg-code-bg rounded-lg p-4 overflow-x-auto">
                    <pre className="text-sm text-gray-100">
                      <code>{`// Component-based approach
struct Transform {
    vec2 position;
    float rotation;
    vec2 scale;
};

struct Sprite {
    TextureID texture;
    vec4 color;
    vec2 size;
};

// Systems operate on components
class RenderSystem {
    void update(Registry& registry) {
        auto view = registry.view<Transform, Sprite>();
        for (auto entity : view) {
            auto& transform = view.get<Transform>(entity);
            auto& sprite = view.get<Sprite>(entity);
            render(transform, sprite);
        }
    }
};`}</code>
                    </pre>
                  </div>
                  
                  <div className="grid md:grid-cols-2 gap-4">
                    <div className="bg-green-50 dark:bg-green-900/20 p-4 rounded-lg border border-green-200 dark:border-green-800">
                      <h4 className="font-semibold text-green-800 dark:text-green-300 mb-2">Benefits</h4>
                      <ul className="text-sm space-y-1 text-green-700 dark:text-green-300">
                        <li>• Better cache performance</li>
                        <li>• Easy parallel processing</li>
                        <li>• Flexible entity composition</li>
                        <li>• Easier to maintain and debug</li>
                      </ul>
                    </div>
                    <div className="bg-blue-50 dark:bg-blue-900/20 p-4 rounded-lg border border-blue-200 dark:border-blue-800">
                      <h4 className="font-semibold text-blue-800 dark:text-blue-300 mb-2">Trade-offs</h4>
                      <ul className="text-sm space-y-1 text-blue-700 dark:text-blue-300">
                        <li>• Steeper learning curve</li>
                        <li>• More complex entity relationships</li>
                        <li>• Additional memory overhead for sparse data</li>
                      </ul>
                    </div>
                  </div>
                </CardContent>
              </Card>
            </TabsContent>
            
            <TabsContent value="rendering" className="space-y-6">
              <Card className="border-l-4 border-l-engine-red">
                <CardHeader>
                  <CardTitle className="text-2xl">Batched Rendering Pipeline</CardTitle>
                </CardHeader>
                <CardContent className="space-y-4">
                  <p className="text-muted-foreground leading-relaxed">
                    Implemented sprite batching and texture atlasing to minimize draw calls 
                    and maximize GPU utilization for 2D rendering.
                  </p>
                  
                  <div className="bg-code-bg rounded-lg p-4 overflow-x-auto">
                    <pre className="text-sm text-gray-100">
                      <code>{`class SpriteBatcher {
    struct Vertex {
        vec2 position;
        vec2 texCoords;
        vec4 color;
        float textureIndex;
    };
    
    void flush() {
        if (vertexCount == 0) return;
        
        // Upload vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 
                       vertexCount * sizeof(Vertex), vertices);
        
        // Bind textures
        for (int i = 0; i < textureSlotIndex; i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
        }
        
        // Single draw call for entire batch
        glDrawElements(GL_TRIANGLES, indexCount, 
                      GL_UNSIGNED_INT, nullptr);
    }
};`}</code>
                    </pre>
                  </div>
                  
                  <div className="bg-muted p-4 rounded-lg">
                    <h4 className="font-semibold mb-2">Performance Impact</h4>
                    <p className="text-sm text-muted-foreground">
                      Reduced draw calls from ~1000/frame to ~10/frame for typical 2D scenes, 
                      resulting in 60fps performance on integrated graphics for complex scenes.
                    </p>
                  </div>
                </CardContent>
              </Card>
            </TabsContent>
            
            <TabsContent value="memory" className="space-y-6">
              <Card className="border-l-4 border-l-engine-blue">
                <CardHeader>
                  <CardTitle className="text-2xl">Memory Pool Allocation</CardTitle>
                </CardHeader>
                <CardContent className="space-y-4">
                  <p className="text-muted-foreground leading-relaxed">
                    Custom memory allocators to reduce heap fragmentation and improve 
                    cache locality for game objects with predictable lifetimes.
                  </p>
                  
                  <div className="bg-code-bg rounded-lg p-4 overflow-x-auto">
                    <pre className="text-sm text-gray-100">
                      <code>{`template<typename T, size_t PoolSize>
class ObjectPool {
    alignas(T) char storage[PoolSize * sizeof(T)];
    std::bitset<PoolSize> used;
    
public:
    T* acquire() {
        size_t index = used.find_first_not_set();
        if (index == std::bitset<PoolSize>::npos) 
            return nullptr;
            
        used.set(index);
        return reinterpret_cast<T*>(&storage[index * sizeof(T)]);
    }
    
    void release(T* obj) {
        ptrdiff_t index = (reinterpret_cast<char*>(obj) - storage) / sizeof(T);
        used.reset(index);
        obj->~T();
    }
};`}</code>
                    </pre>
                  </div>
                </CardContent>
              </Card>
            </TabsContent>
            
            <TabsContent value="scripting" className="space-y-6">
              <Card className="border-l-4 border-l-engine-red">
                <CardHeader>
                  <CardTitle className="text-2xl">Lua Integration</CardTitle>
                </CardHeader>
                <CardContent className="space-y-4">
                  <p className="text-muted-foreground leading-relaxed">
                    Embedded Lua for gameplay scripting, allowing rapid iteration without 
                    recompilation while maintaining performance for core systems.
                  </p>
                  
                  <div className="bg-code-bg rounded-lg p-4 overflow-x-auto">
                    <pre className="text-sm text-gray-100">
                      <code>{`-- Lua gameplay script
function onUpdate(entity, deltaTime)
    local transform = getComponent(entity, "Transform")
    local input = getInput()
    
    if input:isKeyPressed("W") then
        transform.position.y = transform.position.y + 100 * deltaTime
    end
    
    -- Smooth camera follow
    local camera = getCamera()
    camera.position = lerp(camera.position, transform.position, 0.1)
end

function onCollision(entity, other)
    if hasComponent(other, "Collectible") then
        destroyEntity(other)
        playSound("collect.wav")
    end
end`}</code>
                    </pre>
                  </div>
                  
                  <div className="bg-muted p-4 rounded-lg">
                    <h4 className="font-semibold mb-2">Why Lua?</h4>
                    <p className="text-sm text-muted-foreground">
                      Lua's lightweight nature, easy C++ integration, and excellent performance 
                      made it ideal for scripting game logic while keeping the engine core in C++.
                    </p>
                  </div>
                </CardContent>
              </Card>
            </TabsContent>
          </Tabs>
        </div>
      </div>
    </section>
  );
};

export default DesignDecisions;
