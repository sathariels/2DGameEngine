
const Footer = () => {
  return (
    <footer className="bg-gray-900 border-t border-gray-800 py-12">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center">
          <div className="flex items-center justify-center space-x-2 mb-6">
            <div className="w-8 h-8 bg-gradient-to-r from-blue-400 to-red-400 rounded-lg"></div>
            <span className="text-xl font-bold text-white">2D Game Engine</span>
          </div>
          
          <p className="text-gray-400 mb-6">
            Built with passion for game development and modern C++ architecture.
          </p>
          
          <div className="flex justify-center space-x-8 mb-8">
            <a href="#hero" className="text-gray-400 hover:text-white transition-colors">Home</a>
            <a href="#demo" className="text-gray-400 hover:text-white transition-colors">Demo</a>
            <a href="#github" className="text-gray-400 hover:text-white transition-colors">GitHub</a>
            <a href="#contact" className="text-gray-400 hover:text-white transition-colors">Contact</a>
          </div>
          
          <div className="border-t border-gray-800 pt-8">
            <p className="text-gray-500">
              © {new Date().getFullYear()} Nithilan. All rights reserved. | 
              <a href="https://nithilan.dev" className="text-blue-400 hover:text-blue-300 ml-1 transition-colors">
                nithilan.dev
              </a>
            </p>
          </div>
        </div>
      </div>
    </footer>
  );
};

export default Footer;
