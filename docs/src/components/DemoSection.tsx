
import { useEffect, useRef } from 'react';
import { Play, ExternalLink, Code } from 'lucide-react';
import { Button } from '@/components/ui/button';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';

export function DemoSection() {
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

    const elements = sectionRef.current?.querySelectorAll('.demo-item');
    elements?.forEach((element) => observer.observe(element));

    return () => observer.disconnect();
  }, []);

  return (
    <section id="demo" ref={sectionRef} className="py-24">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-3xl sm:text-4xl font-bold text-foreground mb-4">
            Engine Demo
          </h2>
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
            See the 2D Game Engine in action with live demonstrations of core features
          </p>
        </div>

        <div className="grid lg:grid-cols-2 gap-12 items-center">
          <div className="demo-item section-fade-in">
            <Card className="glass-card overflow-hidden">
              <div className="aspect-video bg-muted relative">
                {/* Placeholder for engine demo video */}
                <div className="absolute inset-0 bg-gradient-to-br from-accent/20 to-primary/20 flex items-center justify-center">
                  <div className="text-center">
                    <Play className="h-20 w-20 text-accent mb-4 mx-auto animate-float" />
                    <p className="text-xl font-semibold text-foreground">Engine Demo Video</p>
                    <p className="text-sm text-muted-foreground mt-2 px-4">
                      Replace with your actual engine demonstration video
                    </p>
                  </div>
                </div>
                {/* Uncomment and replace with your actual video */}
                {/* 
                <video 
                  className="w-full h-full object-cover" 
                  controls
                  poster="/path-to-your-engine-demo-poster.jpg"
                >
                  <source src="/path-to-your-engine-demo-video.mp4" type="video/mp4" />
                </video>
                */}
              </div>
            </Card>
          </div>

          <div className="demo-item section-fade-in space-y-6">
            <Card className="glass-card">
              <CardHeader>
                <CardTitle className="flex items-center gap-2">
                  <Code className="h-5 w-5 text-primary" />
                  2D Game Engine Features
                </CardTitle>
                <CardDescription>
                  Core functionality demonstrated in real-time
                </CardDescription>
              </CardHeader>
              <CardContent className="space-y-4">
                <div className="space-y-2">
                  <h4 className="font-semibold text-foreground">Live Demonstrations:</h4>
                  <ul className="space-y-1 text-sm text-muted-foreground">
                    <li>• Sprite rendering and animation system</li>
                    <li>• Tilemap rendering and level editing</li>
                    <li>• Physics simulation and collision detection</li>
                    <li>• Input handling and controls</li>
                    <li>• Audio system integration</li>
                    <li>• Performance optimization features</li>
                  </ul>
                </div>
                <div className="flex gap-3">
                  <Button variant="outline" size="sm">
                    <Play className="mr-2 h-4 w-4" />
                    Watch Demo
                  </Button>
                  <Button variant="ghost" size="sm">
                    <ExternalLink className="mr-2 h-4 w-4" />
                    View Source
                  </Button>
                </div>
              </CardContent>
            </Card>

            <Card className="glass-card">
              <CardHeader>
                <CardTitle>Technical Highlights</CardTitle>
              </CardHeader>
              <CardContent>
                <div className="space-y-3 text-sm">
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Rendering</span>
                    <span className="text-foreground">OpenGL/DirectX</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Physics</span>
                    <span className="text-foreground">Custom System</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Audio</span>
                    <span className="text-foreground">OpenAL</span>
                  </div>
                  <div className="flex justify-between">
                    <span className="text-muted-foreground">Platform</span>
                    <span className="text-foreground">Cross-platform</span>
                  </div>
                </div>
              </CardContent>
            </Card>
          </div>
        </div>
      </div>
    </section>
  );
}
