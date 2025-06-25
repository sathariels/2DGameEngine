
import { Github, Download, ExternalLink } from 'lucide-react';

const TryItYourself = () => {
  return (
    <section className="py-20 bg-gray-900">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Try It <span className="text-blue-400">Yourself</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-4xl mx-auto">
            Get hands-on with the engine. Download the source code, explore the documentation, 
            and start building your own 2D games with this powerful foundation.
          </p>
        </div>

        <div className="grid grid-cols-1 lg:grid-cols-2 gap-8">
          {/* Download Section */}
          <div className="bg-black/50 border border-gray-700 rounded-2xl p-8">
            <div className="flex items-center mb-6">
              <Download className="w-8 h-8 text-red-400 mr-3" />
              <h3 className="text-2xl font-bold text-white">Download Engine</h3>
            </div>
            
            <p className="text-gray-300 mb-6 leading-relaxed">
              Complete source code with build scripts, documentation, and example projects. 
              Includes everything you need to start developing games immediately.
            </p>
            
            <div className="space-y-4 mb-6">
              <div className="flex items-center text-gray-300">
                <span className="w-2 h-2 bg-green-400 rounded-full mr-3"></span>
                Full source code (C++)
              </div>
              <div className="flex items-center text-gray-300">
                <span className="w-2 h-2 bg-green-400 rounded-full mr-3"></span>
                CMake build system
              </div>
              <div className="flex items-center text-gray-300">
                <span className="w-2 h-2 bg-green-400 rounded-full mr-3"></span>
                Example projects & tutorials
              </div>
              <div className="flex items-center text-gray-300">
                <span className="w-2 h-2 bg-green-400 rounded-full mr-3"></span>
                Comprehensive documentation
              </div>
            </div>
            
            <button className="w-full bg-red-500 hover:bg-red-600 text-white py-4 rounded-lg font-medium text-lg transition-colors group">
              <span className="flex items-center justify-center">
                <Download className="w-5 h-5 mr-2 group-hover:translate-y-1 transition-transform" />
                Download Latest Release
              </span>
            </button>
          </div>

          {/* GitHub Section */}
          <div className="bg-black/50 border border-gray-700 rounded-2xl p-8">
            <div className="flex items-center mb-6">
              <Github className="w-8 h-8 text-blue-400 mr-3" />
              <h3 className="text-2xl font-bold text-white">GitHub Repository</h3>
            </div>
            
            <p className="text-gray-300 mb-6 leading-relaxed">
              Explore the development process, contribute to the project, or fork it for your own modifications. 
              The repository includes detailed commit history and development insights.
            </p>
            
            <div className="grid grid-cols-2 gap-4 mb-6">
              <div className="bg-gray-800 rounded-lg p-4 text-center">
                <div className="text-2xl font-bold text-blue-400">50+</div>
                <div className="text-gray-400 text-sm">Commits</div>
              </div>
              <div className="bg-gray-800 rounded-lg p-4 text-center">
                <div className="text-2xl font-bold text-red-400">15K+</div>
                <div className="text-gray-400 text-sm">Lines of Code</div>
              </div>
            </div>
            
            <div className="space-y-3">
              <a 
                href="#" 
                className="flex items-center justify-between w-full bg-gray-800 hover:bg-gray-700 p-4 rounded-lg transition-colors group"
              >
                <span className="text-white font-medium">View Source Code</span>
                <ExternalLink className="w-5 h-5 text-gray-400 group-hover:translate-x-1 transition-transform" />
              </a>
              
              <a 
                href="#" 
                className="flex items-center justify-between w-full bg-gray-800 hover:bg-gray-700 p-4 rounded-lg transition-colors group"
              >
                <span className="text-white font-medium">Documentation</span>
                <ExternalLink className="w-5 h-5 text-gray-400 group-hover:translate-x-1 transition-transform" />
              </a>
              
              <a 
                href="#" 
                className="flex items-center justify-between w-full bg-gray-800 hover:bg-gray-700 p-4 rounded-lg transition-colors group"
              >
                <span className="text-white font-medium">Issues & Discussions</span>
                <ExternalLink className="w-5 h-5 text-gray-400 group-hover:translate-x-1 transition-transform" />
              </a>
            </div>
          </div>
        </div>

        {/* Quick Start Guide */}
        <div className="mt-12 bg-black/30 border border-gray-700 rounded-2xl p-8">
          <h3 className="text-2xl font-bold text-white mb-6 text-center">Quick Start Guide</h3>
          <div className="grid grid-cols-1 md:grid-cols-3 gap-6">
            <div className="text-center">
              <div className="w-12 h-12 bg-blue-500/20 border border-blue-500 rounded-full flex items-center justify-center mx-auto mb-4">
                <span className="text-blue-400 font-bold">1</span>
              </div>
              <h4 className="text-white font-medium mb-2">Clone & Build</h4>
              <p className="text-gray-400 text-sm">Download and compile with CMake</p>
            </div>
            <div className="text-center">
              <div className="w-12 h-12 bg-red-500/20 border border-red-500 rounded-full flex items-center justify-center mx-auto mb-4">
                <span className="text-red-400 font-bold">2</span>
              </div>
              <h4 className="text-white font-medium mb-2">Run Examples</h4>
              <p className="text-gray-400 text-sm">Explore included demo projects</p>
            </div>
            <div className="text-center">
              <div className="w-12 h-12 bg-green-500/20 border border-green-500 rounded-full flex items-center justify-center mx-auto mb-4">
                <span className="text-green-400 font-bold">3</span>
              </div>
              <h4 className="text-white font-medium mb-2">Start Creating</h4>
              <p className="text-gray-400 text-sm">Build your first game</p>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default TryItYourself;
