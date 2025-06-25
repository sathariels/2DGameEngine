
import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';

const LiveDemo = () => {
  const openDemo = () => {
    // Replace with actual demo URL when available
    window.open('#', '_blank');
  };

  return (
    <section className="py-20 bg-gray-950" id="demo-section">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            <span className="text-blue-500">Live</span> Demo
          </h2>
          <p className="text-xl text-gray-400 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            Experience the engine firsthand with an interactive demo
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto">
          <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.3s' }}>
            <CardHeader>
              <CardTitle className="text-white text-2xl text-center">
                Interactive Game Demo
              </CardTitle>
            </CardHeader>
            <CardContent className="p-8">
              <div className="aspect-video bg-gray-900 rounded-lg flex items-center justify-center mb-6">
                <div className="text-center">
                  <div className="w-16 h-16 bg-blue-600 rounded-full flex items-center justify-center mx-auto mb-4">
                    <svg className="w-8 h-8 text-white" fill="currentColor" viewBox="0 0 20 20">
                      <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clipRule="evenodd" />
                    </svg>
                  </div>
                  <p className="text-gray-400 mb-4">Demo will be embedded here</p>
                  <p className="text-sm text-gray-500">
                    Replace the demo files in /public/demo/ folder to update
                  </p>
                </div>
              </div>
              
              <div className="text-center">
                <Button 
                  onClick={openDemo}
                  className="bg-blue-600 hover:bg-blue-700 text-white px-6 py-3"
                >
                  Open Full Demo
                </Button>
              </div>
            </CardContent>
          </Card>
        </div>
      </div>
    </section>
  );
};

export default LiveDemo;
