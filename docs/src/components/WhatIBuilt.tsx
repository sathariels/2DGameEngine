
import { Card, CardContent } from '@/components/ui/card';
import { Cpu, Layers, Zap, Code2, Gamepad2, Wrench } from 'lucide-react';

const features = [
  {
    icon: Layers,
    title: "Entity-Component-System Architecture",
    description: "Modular, data-oriented design pattern that separates game logic from data, enabling efficient memory usage and parallel processing."
  },
  {
    icon: Zap,
    title: "High-Performance Rendering",
    description: "Custom OpenGL renderer with sprite batching, texture atlasing, and shader management for optimal GPU utilization."
  },
  {
    icon: Cpu,
    title: "Multi-threaded Systems",
    description: "Parallel processing for physics, rendering, and game logic using modern C++ threading primitives."
  },
  {
    icon: Gamepad2,
    title: "Flexible Input System",
    description: "Unified input handling supporting keyboard, mouse, and gamepad with customizable key bindings and input mapping."
  },
  {
    icon: Code2,
    title: "Scripting Integration",
    description: "Lua scripting support for rapid gameplay prototyping and runtime behavior modification."
  },
  {
    icon: Wrench,
    title: "Developer Tools",
    description: "Built-in profiler, entity inspector, and debug rendering for efficient development and optimization."
  }
];

const technologies = [
  "C++17", "OpenGL 4.6", "GLFW", "GLM", "ImGui", 
  "Lua 5.4", "Box2D", "OpenAL", "stb_image", "JSON"
];

const WhatIBuilt = () => {
  return (
    <section className="py-12 sm:py-16 lg:py-20 bg-muted/50">
      <div className="container mx-auto px-4 sm:px-6">
        <div className="text-center mb-8 sm:mb-12 animate-fade-in-up">
          <h2 className="text-2xl sm:text-3xl lg:text-4xl font-bold mb-4 text-gradient">What I Built</h2>
          <p className="text-base sm:text-lg lg:text-xl text-muted-foreground max-w-3xl mx-auto">
            A comprehensive 2D game engine built from the ground up, addressing real-world 
            game development challenges with modern software engineering practices and 
            performance-oriented design decisions.
          </p>
        </div>
        
        <div className="grid sm:grid-cols-2 lg:grid-cols-3 gap-6 sm:gap-8 mb-12 sm:mb-16 animate-fade-in">
          {features.map((feature, index) => (
            <Card 
              key={index} 
              className="hover:shadow-lg transition-all duration-300 border-l-4 border-l-engine-blue hover:border-l-engine-red group"
            >
              <CardContent className="p-4 sm:p-6">
                <div className="flex items-start space-x-3 sm:space-x-4">
                  <div className="p-2 bg-engine-blue/10 rounded-lg group-hover:bg-engine-red/10 transition-colors duration-300 flex-shrink-0">
                    <feature.icon className="h-5 w-5 sm:h-6 sm:w-6 text-engine-blue group-hover:text-engine-red transition-colors duration-300" />
                  </div>
                  <div>
                    <h3 className="text-base sm:text-lg font-semibold mb-2">{feature.title}</h3>
                    <p className="text-muted-foreground text-xs sm:text-sm leading-relaxed">{feature.description}</p>
                  </div>
                </div>
              </CardContent>
            </Card>
          ))}
        </div>
        
        <div className="animate-fade-in">
          <Card className="bg-background border-2 border-engine-blue/20">
            <CardContent className="p-6 sm:p-8">
              <h3 className="text-xl sm:text-2xl font-bold mb-4 sm:mb-6 text-center">Technologies & Libraries</h3>
              <div className="flex flex-wrap justify-center gap-2 sm:gap-3">
                {technologies.map((tech, index) => (
                  <span 
                    key={index}
                    className="px-3 sm:px-4 py-1 sm:py-2 bg-tech-gray text-white rounded-full text-xs sm:text-sm font-medium hover:bg-engine-blue transition-colors duration-200 cursor-default"
                  >
                    {tech}
                  </span>
                ))}
              </div>
            </CardContent>
          </Card>
        </div>
        
        <div className="mt-8 sm:mt-12 animate-fade-in">
          <Card className="bg-gradient-to-r from-engine-blue/5 to-engine-red/5 border-engine-blue/30">
            <CardContent className="p-6 sm:p-8">
              <h3 className="text-xl sm:text-2xl font-bold mb-4">Problem Statement</h3>
              <p className="text-sm sm:text-base lg:text-lg text-muted-foreground leading-relaxed">
                Existing game engines often come with unnecessary overhead for 2D games, 
                or lack the flexibility needed for custom gameplay mechanics. This engine 
                was designed to provide maximum performance for 2D games while maintaining 
                the flexibility to implement any game concept efficiently. The ECS architecture 
                ensures scalability from simple prototypes to complex, data-heavy games.
              </p>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default WhatIBuilt;
