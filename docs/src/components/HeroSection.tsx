
import React from 'react';
import { Button } from '@/components/ui/button';

const HeroSection = () => {
  const scrollToDemo = () => {
    const demoSection = document.getElementById('demo-section');
    demoSection?.scrollIntoView({ behavior: 'smooth' });
  };

  return (
    <section className="relative min-h-screen flex items-center justify-center overflow-hidden">
      {/* YouTube Background Video */}
      <div className="absolute inset-0 w-full h-full">
        <div className="relative w-full h-full">
          <iframe
            className="absolute top-1/2 left-1/2 w-[300%] h-[300%] -translate-x-1/2 -translate-y-1/2 pointer-events-none"
            src="https://www.youtube.com/embed/dQw4w9WgXcQ?autoplay=1&mute=1&loop=1&playlist=dQw4w9WgXcQ&controls=0&showinfo=0&rel=0&iv_load_policy=3&modestbranding=1"
            title="Game Engine Demo Background"
            allow="autoplay; encrypted-media"
            style={{ filter: 'brightness(0.3)' }}
          />
        </div>
      </div>
      
      {/* Gradient Overlay */}
      <div className="absolute inset-0 hero-gradient" />
      
      {/* Content */}
      <div className="relative z-10 text-center px-6 max-w-6xl mx-auto">
        <h1 className="text-5xl md:text-7xl font-bold text-white mb-6 animate-fade-in-up">
          Custom <span className="text-red-500">2D Game Engine</span>
          <br />
          by <span className="text-blue-500">Nithilan</span>
        </h1>
        
        <p className="text-xl md:text-2xl text-gray-300 mb-8 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
          Built from scratch with modern C++ and advanced rendering techniques
        </p>
        
        <Button 
          onClick={scrollToDemo}
          size="lg"
          className="bg-red-600 hover:bg-red-700 text-white px-8 py-4 text-lg font-semibold animate-fade-in-up"
          style={{ animationDelay: '0.4s' }}
        >
          Watch Demo
        </Button>
      </div>
      
      {/* Scroll Indicator */}
      <div className="absolute bottom-8 left-1/2 transform -translate-x-1/2 animate-bounce">
        <div className="w-6 h-10 border-2 border-white/50 rounded-full flex justify-center">
          <div className="w-1 h-3 bg-white rounded-full mt-2"></div>
        </div>
      </div>
    </section>
  );
};

export default HeroSection;
