
# Demo Directory

Place your interactive demo files here:

## Web Demo Structure:
```
demo/
├── index.html          # Main demo entry point
├── js/                 # JavaScript/WASM files
├── assets/             # Demo assets (textures, sounds)
└── css/                # Demo styling
```

## Integration:
1. Place your built web demo in this directory
2. Update the `LiveDemo.tsx` component to embed or link to your demo
3. The demo will be accessible at `/assets/demo/`

## WASM/Emscripten:
If using Emscripten to compile your C++ engine to WebAssembly:
1. Build your engine with Emscripten
2. Place the generated files (.wasm, .js, .html) here
3. Update the iframe src in LiveDemo component

## Alternative Hosting:
You can also host the demo separately and link to it via the "Open Full Demo" button.
