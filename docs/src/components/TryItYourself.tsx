
import { Download, Github, BookOpen } from 'lucide-react';

const TryItYourself = () => {
  return (
    <section className="py-20 bg-gray-900">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Try It <span className="text-red-400">Yourself</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-3xl mx-auto">
            Get your hands on the engine and start building your own games. Complete source code, documentation, and examples included.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-3 gap-8 mb-12">
          <div className="bg-black/50 border border-gray-700 rounded-xl p-6 text-center hover:border-blue-500/50 transition-all duration-300">
            <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4">
              <Github className="w-8 h-8 text-blue-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-3">Source Code</h3>
            <p className="text-gray-300 mb-4">Full C++ source code with comprehensive comments and clean architecture</p>
            <a 
              href="https://github.com/nithilan" 
              target="_blank" 
              rel="noopener noreferrer"
              className="inline-block bg-blue-500 hover:bg-blue-600 text-white px-6 py-2 rounded-lg font-medium transition-colors"
            >
              View on GitHub
            </a>
          </div>

          <div className="bg-black/50 border border-gray-700 rounded-xl p-6 text-center hover:border-red-500/50 transition-all duration-300">
            <div className="w-16 h-16 bg-red-500/20 rounded-full flex items-center justify-center mx-auto mb-4">
              <Download className="w-8 h-8 text-red-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-3">Download Build</h3>
            <p className="text-gray-300 mb-4">Pre-compiled binaries for Windows and Linux with example projects</p>
            <button className="bg-red-500 hover:bg-red-600 text-white px-6 py-2 rounded-lg font-medium transition-colors">
              Download v1.0
            </button>
          </div>

          <div className="bg-black/50 border border-gray-700 rounded-xl p-6 text-center hover:border-blue-500/50 transition-all duration-300">
            <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4">
              <BookOpen className="w-8 h-8 text-blue-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-3">Documentation</h3>
            <p className="text-gray-300 mb-4">Detailed API documentation and step-by-step tutorials</p>
            <button className="border border-blue-400 text-blue-400 hover:bg-blue-400 hover:text-black px-6 py-2 rounded-lg font-medium transition-colors">
              Read Docs
            </button>
          </div>
        </div>

        <div className="bg-black/30 border border-gray-700 rounded-2xl p-8">
          <h3 className="text-2xl font-bold text-white mb-6">Getting Started</h3>
          <div className="grid grid-cols-1 md:grid-cols-2 gap-8">
            <div>
              <h4 className="text-lg font-semibold text-blue-400 mb-3">Quick Setup</h4>
              <ol className="text-gray-300 space-y-2">
                <li>1. Clone the repository</li>
                <li>2. Install dependencies (CMake, OpenGL)</li>
                <li>3. Build with CMake</li>
                <li>4. Run the example project</li>
              </ol>
            </div>
            <div>
              <h4 className="text-lg font-semibold text-red-400 mb-3">Requirements</h4>
              <ul className="text-gray-300 space-y-2">
                <li>• C++17 compatible compiler</li>
                <li>• OpenGL 4.6 or higher</li>
                <li>• CMake 3.16+</li>
                <li>• 4GB RAM minimum</li>
              </ul>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default TryItYourself;
