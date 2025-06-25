
import { useState } from 'react';

const DesignDecisions = () => {
  const [activeTab, setActiveTab] = useState(0);

  const decisions = [
    {
      title: "Entity Component System",
      problem: "Traditional inheritance-based game object hierarchies become unwieldy and inflexible as games grow in complexity.",
      solution: "Implemented a data-oriented ECS pattern for better cache performance and component composition.",
      code: `// Component definition
struct Transform {
    Vector2 position{0.0f, 0.0f};
    float rotation{0.0f};
    Vector2 scale{1.0f, 1.0f};
};

// System processing
void RenderSystem::Update(EntityManager& entities) {
    auto view = entities.GetView<Transform, Sprite>();
    for (auto entity : view) {
        auto& transform = view.get<Transform>(entity);
        auto& sprite = view.get<Sprite>(entity);
        renderer.Draw(sprite, transform);
    }
}`,
      benefits: ["Better cache locality", "Flexible component composition", "Easy to parallelize", "Memory efficient"]
    },
    {
      title: "Batch Rendering",
      problem: "Individual draw calls for each sprite create significant GPU overhead and limit performance.",
      solution: "Implemented texture atlas batching with dynamic vertex buffer management for optimal draw call reduction.",
      code: `class SpriteBatch {
private:
    std::vector<Vertex> vertices;
    GLuint VBO, VAO, EBO;
    Texture currentTexture;
    
public:
    void Begin() { vertices.clear(); }
    
    void Draw(const Sprite& sprite, const Transform& transform) {
        if (sprite.texture != currentTexture) {
            Flush(); // Draw current batch
            currentTexture = sprite.texture;
        }
        AddQuad(sprite, transform);
    }
    
    void End() { Flush(); }
};`,
      benefits: ["Reduced draw calls", "Higher frame rates", "Better GPU utilization", "Scalable rendering"]
    },
    {
      title: "Resource Management",
      problem: "Manual resource loading and cleanup leads to memory leaks and loading bottlenecks.",
      solution: "Created an automated asset pipeline with reference counting and lazy loading for optimal memory usage.",
      code: `template<typename T>
class ResourceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<T>> resources;
    
public:
    std::shared_ptr<T> Load(const std::string& path) {
        auto it = resources.find(path);
        if (it != resources.end()) {
            return it->second; // Return cached resource
        }
        
        auto resource = std::make_shared<T>();
        if (resource->LoadFromFile(path)) {
            resources[path] = resource;
            return resource;
        }
        return nullptr;
    }
};`,
      benefits: ["Automatic cleanup", "Shared resources", "Fast loading", "Memory optimization"]
    }
  ];

  return (
    <section className="py-20 bg-black">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Design <span className="text-red-400">Decisions</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-4xl mx-auto">
            Every major architectural choice was made with performance, maintainability, and scalability in mind. 
            Here are the key decisions that shaped the engine's design.
          </p>
        </div>

        {/* Tab Navigation */}
        <div className="flex flex-wrap justify-center mb-8 bg-gray-900 rounded-xl p-2">
          {decisions.map((decision, index) => (
            <button
              key={index}
              onClick={() => setActiveTab(index)}
              className={`px-6 py-3 rounded-lg font-medium transition-all duration-300 ${
                activeTab === index 
                  ? 'bg-blue-500 text-white' 
                  : 'text-gray-400 hover:text-white hover:bg-gray-800'
              }`}
            >
              {decision.title}
            </button>
          ))}
        </div>

        {/* Active Tab Content */}
        <div className="bg-gray-900 rounded-2xl overflow-hidden">
          <div className="p-8">
            <h3 className="text-3xl font-bold text-white mb-6">{decisions[activeTab].title}</h3>
            
            <div className="grid grid-cols-1 lg:grid-cols-2 gap-8 mb-8">
              <div>
                <h4 className="text-xl font-bold text-red-400 mb-4">The Problem</h4>
                <p className="text-gray-300 leading-relaxed mb-6">
                  {decisions[activeTab].problem}
                </p>
                
                <h4 className="text-xl font-bold text-blue-400 mb-4">The Solution</h4>
                <p className="text-gray-300 leading-relaxed">
                  {decisions[activeTab].solution}
                </p>
              </div>
              
              <div>
                <h4 className="text-xl font-bold text-white mb-4">Implementation</h4>
                <div className="bg-black border border-gray-700 rounded-lg p-4 overflow-x-auto">
                  <pre className="text-sm text-gray-300">
                    <code>{decisions[activeTab].code}</code>
                  </pre>
                </div>
              </div>
            </div>
            
            <div>
              <h4 className="text-xl font-bold text-white mb-4">Key Benefits</h4>
              <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
                {decisions[activeTab].benefits.map((benefit, index) => (
                  <div key={index} className="bg-black/50 border border-gray-700 rounded-lg p-4 text-center">
                    <span className="text-green-400 font-medium">{benefit}</span>
                  </div>
                ))}
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default DesignDecisions;
