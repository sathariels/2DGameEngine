
import { useState, useEffect } from 'react';
import { Button } from '@/components/ui/button';
import { Moon, Sun, Menu, X } from 'lucide-react';

const Header = () => {
  const [isDark, setIsDark] = useState(false);
  const [isMobileMenuOpen, setIsMobileMenuOpen] = useState(false);

  useEffect(() => {
    const savedTheme = localStorage.getItem('theme');
    const systemPrefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
    
    if (savedTheme === 'dark' || (!savedTheme && systemPrefersDark)) {
      setIsDark(true);
      document.documentElement.classList.add('dark');
    }
  }, []);

  const toggleTheme = () => {
    const newTheme = !isDark;
    setIsDark(newTheme);
    
    if (newTheme) {
      document.documentElement.classList.add('dark');
      localStorage.setItem('theme', 'dark');
    } else {
      document.documentElement.classList.remove('dark');
      localStorage.setItem('theme', 'light');
    }
  };

  const scrollToSection = (sectionId: string) => {
    document.getElementById(sectionId)?.scrollIntoView({ behavior: 'smooth' });
    setIsMobileMenuOpen(false);
  };

  return (
    <header className="fixed top-0 left-0 right-0 z-50 bg-background/80 backdrop-blur-md border-b border-border">
      <div className="container mx-auto px-4 sm:px-6 py-4">
        <div className="flex justify-between items-center">
          <div className="text-lg sm:text-xl font-bold text-gradient">
            2D Game Engine
          </div>
          
          {/* Desktop Navigation */}
          <div className="hidden md:flex items-center gap-6">
            <nav className="flex items-center gap-4">
              <button 
                onClick={() => scrollToSection('demo-section')}
                className="text-sm font-medium hover:text-engine-blue transition-colors duration-200"
              >
                Demo
              </button>
              <button 
                onClick={() => scrollToSection('github-section')}
                className="text-sm font-medium hover:text-engine-blue transition-colors duration-200"
              >
                Code
              </button>
            </nav>
            
            <Button
              variant="ghost"
              size="icon"
              onClick={toggleTheme}
              className="hover:bg-accent"
            >
              {isDark ? <Sun className="h-5 w-5" /> : <Moon className="h-5 w-5" />}
            </Button>
            
            <a 
              href="https://nithilan.dev" 
              target="_blank" 
              rel="noopener noreferrer"
              className="text-sm font-medium hover:text-engine-blue transition-colors duration-200"
            >
              Nithilan's Website
            </a>
          </div>

          {/* Mobile Navigation */}
          <div className="md:hidden flex items-center gap-2">
            <Button
              variant="ghost"
              size="icon"
              onClick={toggleTheme}
              className="hover:bg-accent"
            >
              {isDark ? <Sun className="h-5 w-5" /> : <Moon className="h-5 w-5" />}
            </Button>
            
            <Button
              variant="ghost"
              size="icon"
              onClick={() => setIsMobileMenuOpen(!isMobileMenuOpen)}
              className="hover:bg-accent"
            >
              {isMobileMenuOpen ? <X className="h-5 w-5" /> : <Menu className="h-5 w-5" />}
            </Button>
          </div>
        </div>

        {/* Mobile Menu */}
        {isMobileMenuOpen && (
          <div className="md:hidden mt-4 pb-4 border-t border-border">
            <nav className="flex flex-col gap-4 pt-4">
              <button 
                onClick={() => scrollToSection('demo-section')}
                className="text-left text-sm font-medium hover:text-engine-blue transition-colors duration-200"
              >
                Demo
              </button>
              <button 
                onClick={() => scrollToSection('github-section')}
                className="text-left text-sm font-medium hover:text-engine-blue transition-colors duration-200"
              >
                Code
              </button>
              <a 
                href="https://nithilan.dev" 
                target="_blank" 
                rel="noopener noreferrer"
                className="text-left text-sm font-medium hover:text-engine-blue transition-colors duration-200"
                onClick={() => setIsMobileMenuOpen(false)}
              >
                Nithilan's Website
              </a>
            </nav>
          </div>
        )}
      </div>
    </header>
  );
};

export default Header;
