
import { useState } from 'react';
import { Play, ChevronDown } from 'lucide-react';

const HeroSection = () => {
  const [videoLoaded, setVideoLoaded] = useState(false);

  const scrollToDemo = () => {
    document.getElementById('demo')?.scrollIntoView({ behavior: 'smooth' });
  };

  return (
    <section className="relative min-h-screen flex items-center justify-center overflow-hidden">
      {/* Background Video Container */}
      <div className="absolute inset-0 w-full h-full">
        <div className="relative w-full h-full bg-gradient-to-br from-black via-gray-900 to-black">
          {/* Placeholder for background video */}
          <div className="absolute inset-0 bg-gradient-to-r from-blue-900/20 to-red-900/20" />
          
          {/* Animated grid pattern */}
          <div className="absolute inset-0 opacity-20">
            <div 
              className="w-full h-full animate-pulse"
              style={{
                backgroundImage: `url("data:image/svg+xml,%3Csvg width='60' height='60' viewBox='0 0 60 60' xmlns='http://www.w3.org/2000/svg'%3E%3Cg fill='none' fill-rule='evenodd'%3E%3Cg fill='%234F46E5' fill-opacity='0.1'%3E%3Ccircle cx='30' cy='30' r='1'/%3E%3C/g%3E%3C/g%3E%3C/svg%3E")`
              }}
            />
          </div>
        </div>
      </div>

      {/* Content */}
      <div className="relative z-10 text-center px-4 sm:px-6 lg:px-8 max-w-5xl mx-auto">
        <div className="animate-fade-in">
          <h1 className="text-4xl sm:text-6xl lg:text-7xl font-bold text-white mb-6 leading-tight">
            Custom <span className="text-blue-400">2D Game Engine</span>
            <br />
            by <span className="text-red-400">Nithilan</span>
          </h1>
          
          <p className="text-xl sm:text-2xl text-gray-300 mb-8 max-w-3xl mx-auto">
            A high-performance, modular game engine built from scratch with modern C++ and cutting-edge graphics programming techniques.
          </p>
          
          <div className="flex flex-col sm:flex-row gap-4 justify-center items-center">
            <button 
              onClick={scrollToDemo}
              className="group bg-red-500 hover:bg-red-600 text-white px-8 py-4 rounded-lg text-lg font-medium transition-all duration-300 transform hover:scale-105 hover:shadow-2xl hover:shadow-red-500/25"
            >
              <span className="flex items-center space-x-2">
                <Play className="w-5 h-5 group-hover:translate-x-1 transition-transform" />
                <span>Watch Demo</span>
              </span>
            </button>
            
            <a 
              href="#github" 
              className="group border-2 border-blue-400 text-blue-400 hover:bg-blue-400 hover:text-black px-8 py-4 rounded-lg text-lg font-medium transition-all duration-300"
            >
              View Source Code
            </a>
          </div>
        </div>
      </div>

      {/* Scroll indicator */}
      <div className="absolute bottom-8 left-1/2 transform -translate-x-1/2 animate-bounce">
        <ChevronDown className="w-8 h-8 text-white/60" />
      </div>
    </section>
  );
};

export default HeroSection;
