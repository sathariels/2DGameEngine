
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Github, Download, Book, ExternalLink } from 'lucide-react';

const TryItYourself = () => {
  return (
    <section id="github-section" className="py-12 sm:py-16 lg:py-20 bg-muted/30">
      <div className="container mx-auto px-4 sm:px-6">
        <div className="text-center mb-8 sm:mb-12 animate-fade-in-up">
          <h2 className="text-2xl sm:text-3xl lg:text-4xl font-bold mb-4 text-gradient">Try It Yourself</h2>
          <p className="text-base sm:text-lg lg:text-xl text-muted-foreground max-w-2xl mx-auto">
            Get hands-on with the engine. Download the source code, run the examples, 
            and start building your own 2D games.
          </p>
        </div>
        
        <div className="grid sm:grid-cols-2 lg:grid-cols-3 gap-6 sm:gap-8 max-w-6xl mx-auto animate-fade-in">
          <Card className="hover:shadow-lg transition-all duration-300 border-2 border-engine-blue/20 hover:border-engine-blue/40 group">
            <CardHeader className="text-center">
              <div className="p-3 bg-engine-blue/10 rounded-full w-12 h-12 sm:w-16 sm:h-16 mx-auto mb-4 group-hover:bg-engine-blue/20 transition-colors duration-300">
                <Github className="h-6 w-6 sm:h-10 sm:w-10 text-engine-blue mx-auto mt-0 sm:mt-1" />
              </div>
              <CardTitle className="text-lg sm:text-xl">Source Code</CardTitle>
            </CardHeader>
            <CardContent className="text-center space-y-4">
              <p className="text-sm sm:text-base text-muted-foreground">
                Complete source code with comprehensive documentation, 
                build instructions, and example projects.
              </p>
              <Button 
                className="w-full bg-engine-blue hover:bg-engine-blue/90 text-white"
                onClick={() => window.open('https://github.com/yourusername/2d-game-engine', '_blank')}
              >
                <Github className="mr-2 h-4 w-4" />
                View on GitHub
              </Button>
            </CardContent>
          </Card>
          
          <Card className="hover:shadow-lg transition-all duration-300 border-2 border-engine-red/20 hover:border-engine-red/40 group">
            <CardHeader className="text-center">
              <div className="p-3 bg-engine-red/10 rounded-full w-12 h-12 sm:w-16 sm:h-16 mx-auto mb-4 group-hover:bg-engine-red/20 transition-colors duration-300">
                <Download className="h-6 w-6 sm:h-10 sm:w-10 text-engine-red mx-auto mt-0 sm:mt-1" />
              </div>
              <CardTitle className="text-lg sm:text-xl">Releases</CardTitle>
            </CardHeader>
            <CardContent className="text-center space-y-4">
              <p className="text-sm sm:text-base text-muted-foreground">
                Pre-built binaries, sample games, and development tools 
                ready to run on Windows, macOS, and Linux.
              </p>
              <Button 
                variant="outline" 
                className="w-full border-engine-red text-engine-red hover:bg-engine-red hover:text-white"
                onClick={() => window.open('https://github.com/yourusername/2d-game-engine/releases', '_blank')}
              >
                <Download className="mr-2 h-4 w-4" />
                Download Latest
              </Button>
            </CardContent>
          </Card>
          
          <Card className="hover:shadow-lg transition-all duration-300 border-2 border-engine-blue/20 hover:border-engine-blue/40 group sm:col-span-2 lg:col-span-1">
            <CardHeader className="text-center">
              <div className="p-3 bg-engine-blue/10 rounded-full w-12 h-12 sm:w-16 sm:h-16 mx-auto mb-4 group-hover:bg-engine-blue/20 transition-colors duration-300">
                <Book className="h-6 w-6 sm:h-10 sm:w-10 text-engine-blue mx-auto mt-0 sm:mt-1" />
              </div>
              <CardTitle className="text-lg sm:text-xl">Documentation</CardTitle>
            </CardHeader>
            <CardContent className="text-center space-y-4">
              <p className="text-sm sm:text-base text-muted-foreground">
                Comprehensive guides covering architecture, API reference, 
                tutorials, and best practices for game development.
              </p>
              <Button 
                variant="outline" 
                className="w-full border-engine-blue text-engine-blue hover:bg-engine-blue hover:text-white"
                onClick={() => window.open('https://yourusername.github.io/2d-game-engine-docs', '_blank')}
              >
                <Book className="mr-2 h-4 w-4" />
                Read Docs
              </Button>
            </CardContent>
          </Card>
        </div>
        
        <div className="mt-8 sm:mt-12 animate-fade-in">
          <Card className="bg-gradient-to-r from-tech-gray to-gray-800 text-white max-w-4xl mx-auto">
            <CardContent className="p-6 sm:p-8">
              <h3 className="text-xl sm:text-2xl font-bold mb-4 text-center">Quick Start</h3>
              <div className="bg-black/30 rounded-lg p-4 font-mono text-xs sm:text-sm overflow-x-auto">
                <div className="space-y-2">
                  <div className="text-gray-400"># Clone the repository</div>
                  <div className="break-all">git clone https://github.com/yourusername/2d-game-engine.git</div>
                  <div className="text-gray-400"># Build the engine</div>
                  <div>cd 2d-game-engine && mkdir build && cd build</div>
                  <div>cmake .. && make -j4</div>
                  <div className="text-gray-400"># Run the example game</div>
                  <div>./examples/platformer/platformer</div>
                </div>
              </div>
              
              <div className="mt-6 text-center">
                <Button 
                  variant="outline" 
                  className="w-full sm:w-auto border-white text-white hover:bg-white hover:text-gray-800"
                  onClick={() => window.open('https://github.com/yourusername/2d-game-engine#getting-started', '_blank')}
                >
                  <ExternalLink className="mr-2 h-4 w-4" />
                  Full Setup Guide
                </Button>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default TryItYourself;
