
# Videos Directory

Place your showcase and demo videos here:

- `engine-showcase.mp4` - Main engine features demonstration
- `gameplay-demo.mp4` - Sample gameplay footage
- `technical-overview.mp4` - Technical deep-dive video

## YouTube Integration

The website is currently configured to use YouTube videos. To use your own videos:

1. Upload your videos to YouTube
2. Copy the video ID from the YouTube URL
3. Replace the video IDs in the components:
   - HeroSection.tsx (background video)
   - VideoShowcase.tsx (main showcase video)

## Local Video Files

To use local video files instead of YouTube:
1. Place your video files in this directory
2. Update the video components to use HTML5 video elements
3. Reference videos using `/assets/videos/your-video.mp4`
