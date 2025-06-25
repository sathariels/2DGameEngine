
# Demo Directory

Place your playable game demo files here.

## Structure:
- `index.html` - Main demo HTML file (will be opened in new tab)
- `js/` - JavaScript/WebAssembly game files
- `assets/` - Game assets (sprites, sounds, etc.)
- `demo-build.zip` - Downloadable demo package

## Integration:
The LiveDemo component will:
1. Open `/assets/demo/index.html` in a new tab when "Open Demo" is clicked
2. Download `/assets/demo/demo-build.zip` when "Download Demo" is clicked

Update the file paths in `src/components/LiveDemo.tsx` if you use different names.

## Web Assembly:
If your engine compiles to WebAssembly, place the .wasm files here along with the JavaScript wrapper.
