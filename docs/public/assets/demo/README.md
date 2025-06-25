
# Demo Folder

Place your interactive demo files here:

## Structure:
```
demo/
├── index.html          # Main demo entry point
├── js/
│   ├── game.js         # Compiled game code
│   └── engine.js       # Engine runtime
├── assets/
│   ├── sprites/        # Game sprites
│   ├── audio/          # Game audio files
│   └── data/           # Game data files
└── css/
    └── style.css       # Demo styling
```

## Integration:
The demo will be embedded using an iframe in the LiveDemo component:

```html
<iframe 
  src="/assets/demo/index.html" 
  className="w-full h-full border-0"
  title="Game Engine Demo"
  allowFullScreen
/>
```

## Demo Requirements:
- Should be self-contained in this folder
- Include all necessary assets and dependencies
- Optimize for web delivery (keep file sizes reasonable)
- Ensure it works in modern browsers
- Consider mobile responsiveness

## Alternative:
If you prefer to host the demo externally, update the iframe src to point to your hosted demo URL.
