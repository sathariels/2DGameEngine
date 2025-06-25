
const LiveDemo = () => {
  return (
    <section id="demo" className="py-20 bg-black">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Try the <span className="text-red-400">Engine</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-3xl mx-auto">
            Experience the engine firsthand with this interactive demo built using the same systems and tools.
          </p>
        </div>

        <div className="bg-gray-900 rounded-2xl p-8 shadow-2xl">
          <div className="relative aspect-video rounded-xl overflow-hidden bg-gradient-to-br from-gray-800 to-gray-900 border border-gray-700">
            {/* Demo iframe container */}
            <div className="absolute inset-0 flex items-center justify-center">
              <div className="text-center">
                <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4">
                  <div className="w-8 h-8 border-4 border-blue-400 border-t-transparent rounded-full animate-spin" />
                </div>
                <p className="text-white text-lg mb-2">Interactive Demo</p>
                <p className="text-gray-400">Upload your demo files to /assets/demo/</p>
              </div>
            </div>
            
            {/* Uncomment when you upload your demo */}
            {/* 
            <iframe 
              src="/assets/demo/index.html" 
              className="w-full h-full border-0"
              title="Game Engine Demo"
              allowFullScreen
            />
            */}
          </div>
          
          <div className="mt-6 flex flex-col sm:flex-row gap-4 justify-center">
            <button className="bg-blue-500 hover:bg-blue-600 text-white px-6 py-3 rounded-lg font-medium transition-colors">
              Open in New Tab
            </button>
            <button className="border border-gray-600 text-gray-300 hover:text-white hover:border-gray-500 px-6 py-3 rounded-lg font-medium transition-colors">
              View Source
            </button>
          </div>
        </div>
      </div>
    </section>
  );
};

export default LiveDemo;
