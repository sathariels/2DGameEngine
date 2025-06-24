
import { Play, Github, Download } from 'lucide-react';
import { Button } from '@/components/ui/button';
import { Card } from '@/components/ui/card';

export function HeroSection() {
  return (
    <section className="min-h-screen flex items-center justify-center hero-gradient pt-16">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8">
        <div className="grid lg:grid-cols-2 gap-12 items-center">
          <div className="text-center lg:text-left animate-fade-in">
            <h1 className="text-4xl sm:text-5xl lg:text-6xl font-bold text-foreground mb-6">
              2D Game Engine
              <span className="block text-primary mt-2">Built from Scratch</span>
            </h1>
            <p className="text-xl text-muted-foreground mb-8 max-w-2xl">
              A custom 2D game engine built with modern C++ featuring advanced tile mapping, 
              sprite rendering, physics simulation, and audio management. Perfect for indie developers 
              and learning enthusiasts.
            </p>
            <div className="flex flex-col sm:flex-row gap-4 justify-center lg:justify-start">
              <Button size="lg" className="animate-glow">
                <Play className="mr-2 h-5 w-5" />
                Watch Demo
              </Button>
              <Button variant="outline" size="lg" asChild>
                <a
                  href="https://github.com/yourusername/2DGameEngine"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="flex items-center"
                >
                  <Github className="mr-2 h-5 w-5" />
                  View Source
                </a>
              </Button>
              <Button variant="secondary" size="lg">
                <Download className="mr-2 h-5 w-5" />
                Download
              </Button>
            </div>
          </div>

          <div className="animate-fade-in-up">
            <Card className="glass-card p-8">
              <div className="aspect-video bg-muted rounded-lg flex items-center justify-center mb-4 relative overflow-hidden">
                {/* Placeholder for your engine video/gif */}
                <div className="absolute inset-0 bg-gradient-to-br from-primary/20 to-accent/20 flex items-center justify-center">
                  <div className="text-center">
                    <Play className="h-16 w-16 text-primary mb-4 mx-auto animate-float" />
                    <p className="text-lg font-semibold text-foreground">Engine Demo Video</p>
                    <p className="text-sm text-muted-foreground mt-2">
                      Replace this placeholder with your engine video/GIF
                    </p>
                  </div>
                </div>
                {/* Uncomment and replace with your actual video */}
                {/* 
                <video 
                  className="w-full h-full object-cover rounded-lg" 
                  autoPlay 
                  muted 
                  loop
                  poster="/path-to-your-poster.jpg"
                >
                  <source src="/path-to-your-video.mp4" type="video/mp4" />
                </video>
                */}
              </div>
              <div className="text-center">
                <h3 className="text-lg font-semibold text-foreground mb-2">Live Engine Demo</h3>
                <p className="text-sm text-muted-foreground">
                  Watch the engine in action with real-time physics and rendering
                </p>
              </div>
            </Card>
          </div>
        </div>
      </div>
    </section>
  );
}
