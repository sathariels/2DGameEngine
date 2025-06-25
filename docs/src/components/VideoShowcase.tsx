
import { Card, CardContent } from '@/components/ui/card';

const VideoShowcase = () => {
  // Replace this with your actual YouTube video ID
  const youtubeVideoId = "dQw4w9WgXcQ"; // Placeholder - replace with your video ID
  
  return (
    <section id="video-showcase" className="py-12 sm:py-16 lg:py-20 bg-muted/30">
      <div className="container mx-auto px-4 sm:px-6">
        <div className="text-center mb-8 sm:mb-12 animate-fade-in-up">
          <h2 className="text-2xl sm:text-3xl lg:text-4xl font-bold mb-4 text-gradient">Engine in Action</h2>
          <p className="text-base sm:text-lg lg:text-xl text-muted-foreground max-w-2xl mx-auto">
            Watch a comprehensive demonstration of the engine's capabilities, 
            from rendering systems to physics simulation and input handling.
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto animate-fade-in">
          <Card className="overflow-hidden shadow-2xl border-2 border-engine-blue/20 hover:border-engine-blue/40 transition-colors duration-300">
            <CardContent className="p-0">
              <div className="relative aspect-video">
                <iframe
                  src={`https://www.youtube.com/embed/${youtubeVideoId}?rel=0&modestbranding=1&fs=1&cc_load_policy=0&iv_load_policy=3&color=white&autohide=0&theme=dark`}
                  title="2D Game Engine Showcase"
                  frameBorder="0"
                  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share"
                  allowFullScreen
                  className="w-full h-full"
                ></iframe>
              </div>
            </CardContent>
          </Card>
          
          <div className="mt-6 sm:mt-8 text-center">
            <p className="text-sm sm:text-base lg:text-lg text-muted-foreground leading-relaxed max-w-3xl mx-auto">
              This demonstration showcases the engine's real-time rendering capabilities, 
              including sprite batching, shader management, and physics integration. 
              You'll see examples of particle systems, collision detection, 
              and the component-based architecture in action.
            </p>
          </div>
        </div>
      </div>
    </section>
  );
};

export default VideoShowcase;
