
import { useState, useEffect } from 'react';
import { Github, ExternalLink } from 'lucide-react';

const Navbar = () => {
  const [isScrolled, setIsScrolled] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 50);
    };
    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, []);

  return (
    <nav className={`fixed top-0 w-full z-50 transition-all duration-300 ${
      isScrolled ? 'bg-black/90 backdrop-blur-sm border-b border-gray-800' : 'bg-transparent'
    }`}>
      <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="flex justify-between items-center h-16">
          <div className="flex items-center space-x-4">
            <Github className="w-6 h-6 text-blue-400" />
            <span className="text-white font-medium">2D Game Engine</span>
          </div>
          
          <a 
            href="https://nithilan.dev" 
            target="_blank" 
            rel="noopener noreferrer"
            className="flex items-center space-x-2 text-white hover:text-blue-400 transition-colors group"
          >
            <span>Nithilan's Website</span>
            <ExternalLink className="w-4 h-4 group-hover:translate-x-1 transition-transform" />
          </a>
        </div>
      </div>
    </nav>
  );
};

export default Navbar;
