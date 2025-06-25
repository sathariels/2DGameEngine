
import React from 'react';

const Footer = () => {
  return (
    <footer className="bg-black border-t border-gray-800 py-12">
      <div className="container mx-auto px-6">
        <div className="text-center">
          <div className="text-2xl font-bold text-white mb-4">
            Custom 2D Game Engine
          </div>
          <p className="text-gray-400 mb-6">
            Built with passion for game development and modern C++
          </p>
          <div className="flex justify-center items-center space-x-4 text-sm text-gray-500">
            <span>© 2024 Nithilan</span>
            <span>•</span>
            <a 
              href="https://nithilan.dev" 
              target="_blank" 
              rel="noopener noreferrer"
              className="hover:text-red-400 transition-colors"
            >
              nithilan.dev
            </a>
          </div>
        </div>
      </div>
    </footer>
  );
};

export default Footer;
