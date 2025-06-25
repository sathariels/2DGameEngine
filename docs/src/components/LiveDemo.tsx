
import { useState } from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { ExternalLink, Download } from 'lucide-react';

const LiveDemo = () => {
  const [isLoading, setIsLoading] = useState(false);

  const handleOpenDemo = () => {
    setIsLoading(true);
    // Replace with your actual demo URL
    window.open('/assets/demo/index.html', '_blank');
    setTimeout(() => setIsLoading(false), 1000);
  };

  const handleDownloadDemo = () => {
    // Replace with your actual demo file path
    const link = document.createElement('a');
    link.href = '/assets/demo/demo-build.zip';
    link.download = 'game-engine-demo.zip';
    link.click();
  };

  return (
    <section id="demo-section" className="py-12 sm:py-16 lg:py-20 bg-background">
      <div className="container mx-auto px-4 sm:px-6">
        <div className="text-center mb-8 sm:mb-12 animate-fade-in-up">
          <h2 className="text-2xl sm:text-3xl lg:text-4xl font-bold mb-4 text-gradient">Interactive Demo</h2>
          <p className="text-base sm:text-lg lg:text-xl text-muted-foreground max-w-2xl mx-auto">
            Experience the engine firsthand with our interactive demo. 
            Test the controls, physics, and rendering systems in real-time.
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto animate-fade-in">
          <Card className="shadow-2xl border-2 border-engine-red/20 hover:border-engine-red/40 transition-all duration-300">
            <CardHeader className="text-center">
              <CardTitle className="text-xl sm:text-2xl">Playable Game Demo</CardTitle>
            </CardHeader>
            <CardContent className="space-y-6">
              {/* Demo iframe placeholder */}
              <div className="aspect-video bg-tech-gray rounded-lg flex items-center justify-center border-2 border-dashed border-gray-600">
                <div className="text-center text-gray-400 p-4">
                  <div className="text-4xl sm:text-6xl mb-4">🎮</div>
                  <p className="text-sm sm:text-lg mb-4">Interactive Demo Will Load Here</p>
                  <p className="text-xs sm:text-sm">Replace this section with your embedded game demo</p>
                </div>
              </div>
              
              <div className="flex flex-col sm:flex-row gap-4 justify-center">
                <Button 
                  onClick={handleOpenDemo}
                  disabled={isLoading}
                  className="w-full sm:w-auto bg-engine-blue hover:bg-engine-blue/90 text-white px-6 py-2"
                >
                  <ExternalLink className="mr-2 h-4 w-4" />
                  {isLoading ? 'Loading...' : 'Open Demo in New Tab'}
                </Button>
                
                <Button 
                  onClick={handleDownloadDemo}
                  variant="outline"
                  className="w-full sm:w-auto border-engine-red text-engine-red hover:bg-engine-red hover:text-white px-6 py-2"
                >
                  <Download className="mr-2 h-4 w-4" />
                  Download Demo
                </Button>
              </div>
              
              <div className="bg-muted p-4 rounded-lg">
                <h4 className="font-semibold mb-2 text-sm sm:text-base">Demo Controls:</h4>
                <ul className="text-xs sm:text-sm text-muted-foreground space-y-1">
                  <li>• WASD or Arrow Keys - Movement</li>
                  <li>• Mouse - Camera control</li>
                  <li>• Space - Jump/Interact</li>
                  <li>• Click objects to interact with physics</li>
                </ul>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default LiveDemo;
