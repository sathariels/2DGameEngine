
import React from 'react';
import { Card, CardContent } from '@/components/ui/card';

const VideoShowcase = () => {
  return (
    <section className="py-20 section-gradient" id="video-showcase">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            Engine in <span className="text-red-500">Action</span>
          </h2>
          <p className="text-xl text-gray-400 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            See the power and flexibility of the custom 2D game engine
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto">
          <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.3s' }}>
            <CardContent className="p-0">
              <div className="relative aspect-video">
                <iframe
                  className="w-full h-full rounded-lg"
                  src="https://www.youtube.com/embed/dQw4w9WgXcQ"
                  title="Game Engine Features Showcase"
                  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                  allowFullScreen
                />
              </div>
            </CardContent>
          </Card>
          
          <div className="mt-8 text-center animate-fade-in-up" style={{ animationDelay: '0.4s' }}>
            <p className="text-gray-300 text-lg leading-relaxed max-w-3xl mx-auto">
              This video demonstrates the core features of the engine including the Entity Component System (ECS), 
              advanced rendering pipeline, physics integration, and real-time asset management. 
              Watch how seamlessly different game objects interact within the engine's architecture.
            </p>
          </div>
        </div>
      </div>
    </section>
  );
};

export default VideoShowcase;
