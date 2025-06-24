
import { useEffect, useRef } from 'react';
import { Cpu, Layers, Zap, Code } from 'lucide-react';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';

const decisions = [
  {
    icon: Cpu,
    title: 'Game Loop Architecture',
    decision: 'Fixed Timestep with Interpolation',
    rationale: 'Ensures consistent physics simulation across different frame rates while maintaining smooth visual output. The engine runs physics at 60Hz fixed timestep but renders at variable framerate with interpolation.',
    alternatives: 'Variable timestep was considered but would cause physics inconsistencies. Semi-fixed timestep was too complex for the scope.',
  },
  {
    icon: Layers,
    title: 'Rendering Pipeline',
    decision: 'OpenGL with Sprite Batching',
    description: 'Modern OpenGL 3.3+ with custom shader system and automatic sprite batching for optimal performance.',
    rationale: 'OpenGL provides cross-platform compatibility while allowing low-level control. Sprite batching dramatically reduces draw calls from thousands to dozens.',
    alternatives: 'DirectX was Windows-only. Vulkan was too complex. SDL2 renderer lacked the flexibility needed.',
  },
  {
    icon: Code,
    title: 'Programming Language',
    decision: 'C++17 with Smart Pointers',
    rationale: 'C++ provides the performance needed for real-time games while C++17 features like smart pointers ensure memory safety. RAII principles prevent resource leaks.',
    alternatives: 'C was too low-level and error-prone. Rust had a steep learning curve. C# required runtime dependency.',
  },
  {
    icon: Zap,
    title: 'Memory Management',
    decision: 'Custom Pool Allocators',
    rationale: 'Game objects have predictable lifetimes and frequent allocation/deallocation. Pool allocators eliminate fragmentation and provide consistent performance.',
    alternatives: 'Standard malloc/free caused fragmentation. Garbage collection would introduce unpredictable pauses.',
  },
];

export function DesignSection() {
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

    const cards = sectionRef.current?.querySelectorAll('.design-card');
    cards?.forEach((card) => observer.observe(card));

    return () => observer.disconnect();
  }, []);

  return (
    <section id="design" ref={sectionRef} className="py-24 bg-muted/30">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-3xl sm:text-4xl font-bold text-foreground mb-4">
            Design Decisions
          </h2>
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
            Key architectural choices that shaped the engine's design and the reasoning behind them
          </p>
        </div>

        <div className="grid lg:grid-cols-2 gap-8">
          {decisions.map((decision, index) => (
            <Card 
              key={decision.title} 
              className={`design-card section-fade-in glass-card hover:shadow-lg transition-all duration-300`}
              style={{ animationDelay: `${index * 0.1}s` }}
            >
              <CardHeader>
                <div className="flex items-center gap-3 mb-2">
                  <div className="w-10 h-10 bg-accent/10 rounded-lg flex items-center justify-center">
                    <decision.icon className="h-5 w-5 text-accent" />
                  </div>
                  <div>
                    <CardTitle className="text-lg">{decision.title}</CardTitle>
                    <CardDescription className="text-primary font-medium">
                      {decision.decision}
                    </CardDescription>
                  </div>
                </div>
              </CardHeader>
              <CardContent className="space-y-4">
                <div>
                  <h4 className="font-semibold text-foreground mb-2">Why This Choice?</h4>
                  <p className="text-sm text-muted-foreground leading-relaxed">
                    {decision.rationale}
                  </p>
                </div>
                {decision.alternatives && (
                  <div>
                    <h4 className="font-semibold text-foreground mb-2">Alternatives Considered</h4>
                    <p className="text-sm text-muted-foreground leading-relaxed">
                      {decision.alternatives}
                    </p>
                  </div>
                )}
              </CardContent>
            </Card>
          ))}
        </div>
      </div>
    </section>
  );
}
