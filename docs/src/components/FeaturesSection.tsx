
import { useEffect, useRef } from 'react';
import { Gamepad2, Image, Zap, Layers, Music, Cog } from 'lucide-react';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';

const features = [
  {
    icon: Layers,
    title: 'Advanced Tile Mapping',
    description: 'Efficient tile-based world rendering with support for multiple layers, collision detection, and optimized culling.',
  },
  {
    icon: Image,
    title: 'Sprite Rendering System',
    description: 'High-performance sprite batching with animation support, texture atlasing, and automatic memory management.',
  },
  {
    icon: Gamepad2,
    title: 'Input Management',
    description: 'Comprehensive input handling for keyboard, mouse, and gamepad with customizable key bindings and input buffering.',
  },
  {
    icon: Zap,
    title: 'Physics Engine',
    description: 'Built-in 2D physics with collision detection, rigid body dynamics, and spatial partitioning for performance.',
  },
  {
    icon: Music,
    title: 'Audio System',
    description: 'Multi-channel audio mixing with support for music, sound effects, and spatial audio positioning.',
  },
  {
    icon: Cog,
    title: 'Component System',
    description: 'Flexible entity-component architecture allowing for modular game object composition and easy extensibility.',
  },
];

export function FeaturesSection() {
  const sectionRef = useRef<HTMLElement>(null);

  useEffect(() => {
    const observer = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            entry.target.classList.add('visible');
          }
        });
      },
      { threshold: 0.1 }
    );

    const cards = sectionRef.current?.querySelectorAll('.feature-card');
    cards?.forEach((card) => observer.observe(card));

    return () => observer.disconnect();
  }, []);

  return (
    <section id="features" ref={sectionRef} className="py-24 bg-muted/30">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-3xl sm:text-4xl font-bold text-foreground mb-4">
            What I Built
          </h2>
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
            A comprehensive 2D game engine with all the essential systems needed to create engaging games
          </p>
        </div>

        <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-8">
          {features.map((feature, index) => (
            <Card 
              key={feature.title} 
              className={`feature-card section-fade-in glass-card hover:scale-105 transition-all duration-300 hover:shadow-lg`}
              style={{ animationDelay: `${index * 0.1}s` }}
            >
              <CardHeader>
                <div className="w-12 h-12 bg-primary/10 rounded-lg flex items-center justify-center mb-4">
                  <feature.icon className="h-6 w-6 text-primary" />
                </div>
                <CardTitle className="text-xl font-semibold">{feature.title}</CardTitle>
              </CardHeader>
              <CardContent>
                <CardDescription className="text-muted-foreground">
                  {feature.description}
                </CardDescription>
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
