
const DesignDecisions = () => {
  const decisions = [
    {
      title: "Entity Component System (ECS)",
      description: "Chose ECS architecture for maximum flexibility and performance",
      reasoning: "Allows for data-oriented design, better cache performance, and modular entity composition",
      code: `class Entity {
  ComponentMask componentMask;
  EntityID id;
};

template<typename T>
class ComponentArray {
  std::array<T, MAX_ENTITIES> components;
  std::unordered_map<EntityID, size_t> entityToIndex;
};`
    },
    {
      title: "Custom Rendering Pipeline",
      description: "Built a batched 2D renderer with automatic sprite sorting",
      reasoning: "Minimizes draw calls and state changes for optimal GPU performance",
      code: `class BatchRenderer {
  void BeginBatch();
  void DrawQuad(const Transform& transform, 
                const Texture& texture);
  void EndBatch();
  void Flush();
};`
    },
    {
      title: "Component-Based Input System",
      description: "Decoupled input handling from game logic using event system",
      reasoning: "Enables flexible input mapping and easy integration with different input devices",
      code: `class InputComponent {
  std::unordered_map<KeyCode, Action> keyBindings;
  std::function<void(Action)> callback;
};`
    }
  ];

  return (
    <section className="py-20 bg-black">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Design <span className="text-blue-400">Decisions</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-4xl mx-auto">
            Key architectural choices that shaped the engine's performance, maintainability, and developer experience.
          </p>
        </div>

        <div className="space-y-12">
          {decisions.map((decision, index) => (
            <div key={index} className="bg-gray-900 rounded-2xl p-8 border border-gray-700">
              <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
                <div>
                  <h3 className="text-2xl font-bold text-white mb-4">{decision.title}</h3>
                  <p className="text-blue-400 text-lg mb-4">{decision.description}</p>
                  <p className="text-gray-300 leading-relaxed">{decision.reasoning}</p>
                </div>
                
                <div className="bg-black/50 rounded-xl p-6 border border-gray-800">
                  <pre className="text-sm text-gray-300 overflow-x-auto">
                    <code>{decision.code}</code>
                  </pre>
                </div>
              </div>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
};

export default DesignDecisions;
