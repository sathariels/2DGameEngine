
import { useState } from 'react';

const VideoShowcase = () => {
  const [isPlaying, setIsPlaying] = useState(false);

  return (
    <section className="py-20 bg-gray-900">
      <div className="max-w-6xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Engine in <span className="text-blue-400">Action</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-3xl mx-auto">
            Watch a comprehensive walkthrough of the engine's core features, from the Entity Component System to the custom rendering pipeline.
          </p>
        </div>

        <div className="relative rounded-2xl overflow-hidden shadow-2xl bg-black">
          {/* Video Player Container */}
          <div className="relative aspect-video">
            {/* Placeholder for video - replace with actual video */}
            <div className="absolute inset-0 bg-gradient-to-br from-blue-600 to-red-600 flex items-center justify-center">
              <div className="text-center">
                <div className="w-20 h-20 bg-white/20 rounded-full flex items-center justify-center mx-auto mb-4 cursor-pointer hover:bg-white/30 transition-colors">
                  <div className="w-0 h-0 border-l-[16px] border-l-white border-y-[10px] border-y-transparent ml-1" />
                </div>
                <p className="text-white text-lg">Engine Demo Video</p>
                <p className="text-white/70">Click to play when video is uploaded</p>
              </div>
            </div>
            
            {/* Uncomment when you upload your video */}
            {/* 
            <video 
              className="w-full h-full object-cover"
              controls
              poster="/assets/images/video-thumbnail.jpg"
            >
              <source src="/assets/videos/engine-showcase.mp4" type="video/mp4" />
              Your browser does not support the video tag.
            </video>
            */}
          </div>

          {/* Video description */}
          <div className="p-8 bg-black/50">
            <h3 className="text-2xl font-bold text-white mb-4">Feature Walkthrough</h3>
            <p className="text-gray-300 text-lg leading-relaxed">
              This video demonstrates the engine's key capabilities including the Entity Component System architecture, 
              real-time 2D rendering with custom shaders, physics simulation, audio integration, and the comprehensive 
              development tools I've built to streamline game development workflows.
            </p>
          </div>
        </div>
      </div>
    </section>
  );
};

export default VideoShowcase;
