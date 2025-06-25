
import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';

const WhatIBuilt = () => {
  const features = [
    {
      title: "Entity Component System",
      description: "Flexible and performant ECS architecture for game object management",
      tech: "C++17, Template Metaprogramming"
    },
    {
      title: "Advanced Rendering",
      description: "Custom OpenGL renderer with batching, instancing, and shader management",
      tech: "OpenGL 4.5, GLSL, ImGui"
    },
    {
      title: "Physics Integration",
      description: "Seamless integration with Box2D for realistic physics simulation",
      tech: "Box2D, Collision Detection"
    },
    {
      title: "Asset Management",
      description: "Hot-reloading asset system with texture atlasing and audio management",
      tech: "STB Image, OpenAL, JSON"
    }
  ];

  return (
    <section className="py-20 section-gradient">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            What I <span className="text-red-500">Built</span>
          </h2>
          <p className="text-xl text-gray-400 max-w-3xl mx-auto animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            A complete 2D game engine built from the ground up, designed to solve real-world 
            game development challenges with modern C++ and industry-standard techniques.
          </p>
        </div>
        
        <div className="grid md:grid-cols-2 gap-8 max-w-6xl mx-auto">
          {features.map((feature, index) => (
            <Card 
              key={feature.title} 
              className="bg-card border-border hover:bg-gray-800/50 transition-colors duration-300 animate-fade-in-up"
              style={{ animationDelay: `${0.3 + index * 0.1}s` }}
            >
              <CardHeader>
                <CardTitle className="text-white text-xl mb-2">
                  {feature.title}
                </CardTitle>
                <p className="text-blue-400 text-sm font-medium">
                  {feature.tech}
                </p>
              </CardHeader>
              <CardContent>
                <p className="text-gray-300 leading-relaxed">
                  {feature.description}
                </p>
              </CardContent>
            </Card>
          ))}
        </div>
        
        <div className="mt-16 max-w-4xl mx-auto">
          <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.7s' }}>
            <CardContent className="p-8">
              <h3 className="text-2xl font-bold text-white mb-4">Technical Challenges Solved</h3>
              <div className="space-y-4 text-gray-300">
                <p>
                  <strong className="text-red-400">Memory Management:</strong> Implemented custom memory pools 
                  and object pooling to eliminate garbage collection pauses and ensure consistent performance.
                </p>
                <p>
                  <strong className="text-blue-400">Rendering Optimization:</strong> Built a batching system 
                  that reduces draw calls by 90%, enabling smooth rendering of thousands of sprites simultaneously.
                </p>
                <p>
                  <strong className="text-red-400">Modular Architecture:</strong> Designed a plugin-based 
                  system that allows for easy extension and customization without modifying core engine code.
                </p>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default WhatIBuilt;
