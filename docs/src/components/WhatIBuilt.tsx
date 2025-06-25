
const WhatIBuilt = () => {
  const features = [
    {
      title: "Entity Component System",
      description: "Flexible, data-oriented architecture for maximum performance and modularity",
      tech: "Modern C++17"
    },
    {
      title: "Custom Rendering Pipeline", 
      description: "OpenGL-based 2D renderer with batch processing and shader abstractions",
      tech: "OpenGL 4.6"
    },
    {
      title: "Physics Integration",
      description: "Box2D integration with custom collision detection and response systems",
      tech: "Box2D"
    },
    {
      title: "Audio System",
      description: "Multi-channel audio with 3D positioning and real-time effects processing",
      tech: "OpenAL"
    },
    {
      title: "Asset Pipeline",
      description: "Automated asset loading, texture atlasing, and resource management",
      tech: "Custom Tools"
    },
    {
      title: "Developer Tools",
      description: "Level editor, debug console, and performance profiling suite",
      tech: "ImGui"
    }
  ];

  return (
    <section className="py-20 bg-gray-900">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            What I <span className="text-blue-400">Built</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-4xl mx-auto">
            A complete 2D game engine built from the ground up, focusing on performance, modularity, and developer experience. 
            Every component was carefully designed to solve real problems in modern game development.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8 mb-16">
          {features.map((feature, index) => (
            <div 
              key={index}
              className="bg-black/50 border border-gray-700 rounded-xl p-6 hover:border-blue-500/50 transition-all duration-300 group hover:transform hover:scale-105"
            >
              <h3 className="text-xl font-bold text-white mb-3 group-hover:text-blue-400 transition-colors">
                {feature.title}
              </h3>
              <p className="text-gray-300 mb-4 leading-relaxed">
                {feature.description}
              </p>
              <span className="inline-block bg-red-500/20 text-red-400 px-3 py-1 rounded-full text-sm font-medium">
                {feature.tech}
              </span>
            </div>
          ))}
        </div>

        <div className="bg-black/30 border border-gray-700 rounded-2xl p-8">
          <h3 className="text-2xl font-bold text-white mb-6">Core Technologies</h3>
          <div className="grid grid-cols-2 md:grid-cols-4 gap-6">
            {["C++17", "OpenGL", "Box2D", "OpenAL", "ImGui", "CMake", "Git", "Visual Studio"].map((tech, index) => (
              <div key={index} className="text-center">
                <div className="bg-blue-500/10 border border-blue-500/30 rounded-lg p-4 hover:bg-blue-500/20 transition-colors">
                  <span className="text-blue-400 font-medium">{tech}</span>
                </div>
              </div>
            ))}
          </div>
        </div>
      </div>
    </section>
  );
};

export default WhatIBuilt;
