
import { useEffect, useRef } from 'react';
import { Github, Download, BookOpen, Terminal } from 'lucide-react';
import { Button } from '@/components/ui/button';
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from '@/components/ui/card';

export function TryItSection() {
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

    const elements = sectionRef.current?.querySelectorAll('.try-item');
    elements?.forEach((element) => observer.observe(element));

    return () => observer.disconnect();
  }, []);

  return (
    <section id="try-it" ref={sectionRef} className="py-24">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-3xl sm:text-4xl font-bold text-foreground mb-4">
            How to Try It
          </h2>
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
            Get started with the 2D Game Engine in just a few minutes
          </p>
        </div>

        <div className="grid lg:grid-cols-2 gap-8">
          <div className="try-item section-fade-in">
            <Card className="glass-card h-full">
              <CardHeader>
                <CardTitle className="flex items-center gap-2">
                  <Github className="h-5 w-5 text-primary" />
                  Get the Source Code
                </CardTitle>
                <CardDescription>
                  Clone the repository and build from source
                </CardDescription>
              </CardHeader>
              <CardContent className="space-y-4">
                <div className="bg-muted/50 p-4 rounded-lg font-mono text-sm">
                  <div className="text-muted-foreground mb-2"># Clone the repository</div>
                  <div>git clone https://github.com/yourusername/2DGameEngine.git</div>
                  <div className="text-muted-foreground mt-3 mb-2"># Build the engine</div>
                  <div>cd 2DGameEngine</div>
                  <div>mkdir build && cd build</div>
                  <div>cmake .. && make</div>
                </div>
                <div className="flex gap-3">
                  <Button asChild>
                    <a
                      href="https://github.com/yourusername/2DGameEngine"
                      target="_blank"
                      rel="noopener noreferrer"
                    >
                      <Github className="mr-2 h-4 w-4" />
                      View on GitHub
                    </a>
                  </Button>
                  <Button variant="outline">
                    <Download className="mr-2 h-4 w-4" />
                    Download ZIP
                  </Button>
                </div>
              </CardContent>
            </Card>
          </div>

          <div className="try-item section-fade-in">
            <Card className="glass-card h-full">
              <CardHeader>
                <CardTitle className="flex items-center gap-2">
                  <BookOpen className="h-5 w-5 text-accent" />
                  Documentation & Tutorials
                </CardTitle>
                <CardDescription>
                  Learn how to use the engine with comprehensive guides
                </CardDescription>
              </CardHeader>
              <CardContent className="space-y-4">
                <div className="space-y-3">
                  <div className="flex items-center justify-between p-3 bg-muted/30 rounded-lg">
                    <span className="text-sm font-medium">Getting Started Guide</span>
                    <span className="text-xs text-muted-foreground">5 min read</span>
                  </div>
                  <div className="flex items-center justify-between p-3 bg-muted/30 rounded-lg">
                    <span className="text-sm font-medium">API Documentation</span>
                    <span className="text-xs text-muted-foreground">Complete reference</span>
                  </div>
                  <div className="flex items-center justify-between p-3 bg-muted/30 rounded-lg">
                    <span className="text-sm font-medium">Example Projects</span>
                    <span className="text-xs text-muted-foreground">3 tutorials</span>
                  </div>
                </div>
                <Button variant="outline" className="w-full">
                  <BookOpen className="mr-2 h-4 w-4" />
                  Read Documentation
                </Button>
              </CardContent>
            </Card>
          </div>
        </div>

        <div className="try-item section-fade-in mt-8">
          <Card className="glass-card">
            <CardHeader>
              <CardTitle className="flex items-center gap-2">
                <Terminal className="h-5 w-5 text-primary" />
                System Requirements
              </CardTitle>
            </CardHeader>
            <CardContent>
              <div className="grid md:grid-cols-3 gap-6">
                <div>
                  <h4 className="font-semibold text-foreground mb-2">Minimum Requirements</h4>
                  <ul className="text-sm text-muted-foreground space-y-1">
                    <li>• C++17 compatible compiler</li>
                    <li>• OpenGL 3.3+ support</li>
                    <li>• 4GB RAM</li>
                    <li>• 500MB disk space</li>
                  </ul>
                </div>
                <div>
                  <h4 className="font-semibold text-foreground mb-2">Dependencies</h4>
                  <ul className="text-sm text-muted-foreground space-y-1">
                    <li>• CMake 3.15+</li>
                    <li>• GLFW3</li>
                    <li>• GLAD</li>
                    <li>• OpenAL Soft</li>
                  </ul>
                </div>
                <div>
                  <h4 className="font-semibold text-foreground mb-2">Supported Platforms</h4>
                  <ul className="text-sm text-muted-foreground space-y-1">
                    <li>• Windows 10/11</li>
                    <li>• macOS 10.14+</li>
                    <li>• Linux (Ubuntu 18.04+)</li>
                    <li>• More platforms coming</li>
                  </ul>
                </div>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
}
