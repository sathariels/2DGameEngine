
import React from 'react';

const Header = () => {
  return (
    <header className="fixed top-0 left-0 right-0 z-50 bg-black/80 backdrop-blur-sm border-b border-white/10">
      <div className="container mx-auto px-6 py-4 flex justify-between items-center">
        <div className="text-2xl font-bold text-white">
          Game Engine
        </div>
        <a 
          href="https://nithilan.dev" 
          target="_blank" 
          rel="noopener noreferrer"
          className="text-white hover:text-red-500 transition-colors duration-300 font-medium"
        >
          Nithilan's Website
        </a>
      </div>
    </header>
  );
};

export default Header;
