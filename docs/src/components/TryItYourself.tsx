
import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Github, Download } from 'lucide-react';

const TryItYourself = () => {
  return (
    <section className="py-20 section-gradient">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            Try It <span className="text-red-500">Yourself</span>
          </h2>
          <p className="text-xl text-gray-400 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            Get started with the engine and explore the source code
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto">
          <div className="grid md:grid-cols-2 gap-8">
            <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.3s' }}>
              <CardHeader>
                <CardTitle className="text-white text-xl flex items-center gap-3">
                  <Download className="w-6 h-6 text-red-500" />
                  Download Engine
                </CardTitle>
              </CardHeader>
              <CardContent className="space-y-4">
                <p className="text-gray-300">
                  Get the complete engine source code, documentation, and example projects.
                </p>
                <ul className="text-gray-400 space-y-2 text-sm">
                  <li>• Complete C++ source code</li>
                  <li>• CMake build system</li>
                  <li>• Example games and demos</li>
                  <li>• Comprehensive documentation</li>
                </ul>
                <Button className="w-full bg-red-600 hover:bg-red-700 text-white">
                  <Download className="w-4 h-4 mr-2" />
                  Download Latest Release
                </Button>
              </CardContent>
            </Card>
            
            <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.4s' }}>
              <CardHeader>
                <CardTitle className="text-white text-xl flex items-center gap-3">
                  <Github className="w-6 h-6 text-blue-500" />
                  Source Code
                </CardTitle>
              </CardHeader>
              <CardContent className="space-y-4">
                <p className="text-gray-300">
                  Explore the full source code, contribute, and follow development progress.
                </p>
                <ul className="text-gray-400 space-y-2 text-sm">
                  <li>• MIT License - free to use</li>
                  <li>• Active development</li>
                  <li>• Issue tracking and discussions</li>
                  <li>• Contribution guidelines</li>
                </ul>
                <Button 
                  variant="outline" 
                  className="w-full border-blue-500 text-blue-400 hover:bg-blue-500 hover:text-white"
                  onClick={() => window.open('https://github.com/nithilan', '_blank')}
                >
                  <Github className="w-4 h-4 mr-2" />
                  View on GitHub
                </Button>
              </CardContent>
            </Card>
          </div>
          
          <Card className="mt-8 bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.5s' }}>
            <CardContent className="p-8">
              <h3 className="text-2xl font-bold text-white mb-4">Getting Started</h3>
              <div className="space-y-4 text-gray-300">
                <div className="bg-gray-900 p-4 rounded-lg">
                  <h4 className="text-blue-400 font-semibold mb-2">Prerequisites:</h4>
                  <p>C++17 compiler, CMake 3.16+, OpenGL 4.5+ drivers</p>
                </div>
                <div className="bg-gray-900 p-4 rounded-lg">
                  <h4 className="text-red-400 font-semibold mb-2">Quick Setup:</h4>
                  <pre className="text-sm overflow-x-auto">
                    <code>{`git clone https://github.com/nithilan/game-engine.git
cd game-engine
mkdir build && cd build
cmake ..
make -j4`}</code>
                  </pre>
                </div>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default TryItYourself;
