
import { Button } from '@/components/ui/button';
import { Play } from 'lucide-react';

const HeroSection = () => {
  const scrollToDemo = () => {
    document.getElementById('demo-section')?.scrollIntoView({ behavior: 'smooth' });
  };

  return (
    <section className="min-h-screen flex items-center justify-center relative overflow-hidden bg-gradient-to-br from-background via-background to-muted">
      {/* Animated background elements */}
      <div className="absolute inset-0 overflow-hidden">
        <div className="absolute -top-40 -right-40 w-80 h-80 bg-engine-blue/10 rounded-full blur-3xl animate-pulse"></div>
        <div className="absolute -bottom-40 -left-40 w-80 h-80 bg-engine-red/10 rounded-full blur-3xl animate-pulse" style={{ animationDelay: '1s' }}></div>
      </div>
      
      <div className="container mx-auto px-4 sm:px-6 text-center relative z-10">
        <div className="animate-fade-in-up">
          <h1 className="text-3xl sm:text-4xl md:text-5xl lg:text-7xl font-bold mb-4 sm:mb-6 hero-text leading-tight">
            Custom 2D Game Engine
            <br />
            <span className="text-gradient">by Nithilan</span>
          </h1>
          
          <p className="text-base sm:text-lg md:text-xl lg:text-2xl text-muted-foreground mb-6 sm:mb-8 max-w-3xl mx-auto px-4">
            A high-performance, entity-component-system based game engine built from scratch 
            with modern C++ and OpenGL. Designed for rapid prototyping and scalable game development.
          </p>
          
          <div className="flex flex-col sm:flex-row gap-4 justify-center items-center px-4">
            <Button 
              onClick={scrollToDemo}
              size="lg" 
              className="w-full sm:w-auto bg-engine-blue hover:bg-engine-blue/90 text-white px-6 sm:px-8 py-3 text-base sm:text-lg font-semibold animate-glow"
            >
              <Play className="mr-2 h-4 w-4 sm:h-5 sm:w-5" />
              Watch Demo
            </Button>
            
            <Button 
              variant="outline" 
              size="lg"
              className="w-full sm:w-auto border-engine-red text-engine-red hover:bg-engine-red hover:text-white px-6 sm:px-8 py-3 text-base sm:text-lg"
              onClick={() => document.getElementById('github-section')?.scrollIntoView({ behavior: 'smooth' })}
            >
              View Source Code
            </Button>
          </div>
        </div>
      </div>
    </section>
  );
};

export default HeroSection;
