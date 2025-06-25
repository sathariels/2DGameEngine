
const Footer = () => {
  return (
    <footer className="bg-tech-gray text-white py-8 sm:py-12">
      <div className="container mx-auto px-4 sm:px-6">
        <div className="flex flex-col md:flex-row justify-between items-center gap-4">
          <div className="text-center md:text-left">
            <h3 className="text-lg sm:text-xl font-bold text-gradient mb-2">2D Game Engine</h3>
            <p className="text-sm sm:text-base text-gray-400">Built with passion for game development</p>
          </div>
          
          <div className="flex flex-col sm:flex-row items-center gap-2 sm:gap-6 text-center">
            <a 
              href="https://nithilan.dev" 
              target="_blank" 
              rel="noopener noreferrer"
              className="text-sm sm:text-base text-gray-400 hover:text-engine-blue transition-colors duration-200"
            >
              nithilan.dev
            </a>
            <span className="text-gray-600 hidden sm:inline">•</span>
            <p className="text-sm sm:text-base text-gray-400">
              © {new Date().getFullYear()} Nithilan. All rights reserved.
            </p>
          </div>
        </div>
      </div>
    </footer>
  );
};

export default Footer;
