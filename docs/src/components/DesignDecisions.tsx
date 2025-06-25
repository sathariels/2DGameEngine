
import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';

const DesignDecisions = () => {
  const decisions = [
    {
      title: "Entity Component System",
      problem: "Traditional inheritance hierarchies become complex and inflexible",
      solution: "Composition over inheritance with data-oriented design",
      code: `class Entity {
  std::vector<std::unique_ptr<Component>> components;
public:
  template<typename T>
  T* GetComponent() {
    // Type-safe component retrieval
  }
};`
    },
    {
      title: "Render Batching",
      problem: "Individual draw calls create GPU bottlenecks",
      solution: "Batch similar objects into single draw calls",
      code: `struct RenderBatch {
  std::vector<Sprite> sprites;
  Texture* texture;
  
  void Flush() {
    // Upload all sprite data at once
    glBufferData(GL_ARRAY_BUFFER, 
                sprites.size() * sizeof(Sprite),
                sprites.data(), GL_DYNAMIC_DRAW);
  }
};`
    },
    {
      title: "Event System",
      problem: "Tight coupling between game systems",
      solution: "Decoupled observer pattern with type-safe events",
      code: `template<typename EventType>
class EventManager {
  std::vector<std::function<void(const EventType&)>> 
    listeners;
public:
  void Emit(const EventType& event) {
    for(auto& listener : listeners) {
      listener(event);
    }
  }
};`
    }
  ];

  return (
    <section className="py-20 bg-gray-950">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            Design <span className="text-blue-500">Decisions</span>
          </h2>
          <p className="text-xl text-gray-400 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            Key architectural choices that make the engine powerful and maintainable
          </p>
        </div>
        
        <div className="max-w-6xl mx-auto space-y-12">
          {decisions.map((decision, index) => (
            <Card 
              key={decision.title}
              className="bg-card border-border animate-fade-in-up overflow-hidden"
              style={{ animationDelay: `${0.3 + index * 0.2}s` }}
            >
              <div className="grid md:grid-cols-2 gap-0">
                <div className="p-6">
                  <CardHeader className="p-0 mb-4">
                    <CardTitle className="text-white text-2xl mb-3">
                      {decision.title}
                    </CardTitle>
                  </CardHeader>
                  <CardContent className="p-0 space-y-4">
                    <div>
                      <h4 className="text-red-400 font-semibold mb-2">Problem:</h4>
                      <p className="text-gray-300">{decision.problem}</p>
                    </div>
                    <div>
                      <h4 className="text-blue-400 font-semibold mb-2">Solution:</h4>
                      <p className="text-gray-300">{decision.solution}</p>
                    </div>
                  </CardContent>
                </div>
                
                <div className="bg-gray-900 p-6 border-l border-gray-800">
                  <h4 className="text-gray-400 text-sm font-medium mb-3 uppercase tracking-wide">
                    Implementation
                  </h4>
                  <pre className="text-sm text-gray-300 overflow-x-auto">
                    <code>{decision.code}</code>
                  </pre>
                </div>
              </div>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
};

export default DesignDecisions;
