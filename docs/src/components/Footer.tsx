
import { Github, Mail, Twitter, Heart } from 'lucide-react';
import { Button } from '@/components/ui/button';

export function Footer() {
  return (
    <footer className="bg-card border-t border-border">
      <div className="container mx-auto px-4 sm:px-6 lg:px-8 py-12">
        <div className="grid md:grid-cols-3 gap-8">
          <div>
            <h3 className="text-lg font-semibold text-foreground mb-4">2DGameEngine</h3>
            <p className="text-sm text-muted-foreground leading-relaxed">
              A modern 2D game engine built from scratch with C++ and OpenGL. 
              Designed for performance, flexibility, and ease of use.
            </p>
          </div>
          
          <div>
            <h4 className="text-sm font-semibold text-foreground mb-4">Quick Links</h4>
            <div className="space-y-2">
              <a href="#features" className="block text-sm text-muted-foreground hover:text-primary transition-colors">
                Features
              </a>
              <a href="#demo" className="block text-sm text-muted-foreground hover:text-primary transition-colors">
                Demo
              </a>
              <a href="#design" className="block text-sm text-muted-foreground hover:text-primary transition-colors">
                Design Decisions
              </a>
              <a href="#try-it" className="block text-sm text-muted-foreground hover:text-primary transition-colors">
                Try It Out
              </a>
            </div>
          </div>
          
          <div>
            <h4 className="text-sm font-semibold text-foreground mb-4">Connect</h4>
            <div className="flex gap-3">
              <Button variant="ghost" size="sm" asChild>
                <a
                  href="https://github.com/yourusername/2DGameEngine"
                  target="_blank"
                  rel="noopener noreferrer"
                >
                  <Github className="h-4 w-4" />
                </a>
              </Button>
              <Button variant="ghost" size="sm" asChild>
                <a href="mailto:your.email@example.com">
                  <Mail className="h-4 w-4" />
                </a>
              </Button>
              <Button variant="ghost" size="sm" asChild>
                <a
                  href="https://twitter.com/yourusername"
                  target="_blank"
                  rel="noopener noreferrer"
                >
                  <Twitter className="h-4 w-4" />
                </a>
              </Button>
            </div>
          </div>
        </div>
        
        <div className="border-t border-border mt-8 pt-8 text-center">
          <p className="text-sm text-muted-foreground flex items-center justify-center gap-1">
            Made with <Heart className="h-4 w-4 text-red-500" /> by Your Name
          </p>
        </div>
      </div>
    </footer>
  );
}
