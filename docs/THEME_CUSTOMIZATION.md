
# Portfolio Theme Customization Guide

This React-based portfolio is designed to be easily customizable like a Jekyll theme. All content and configuration is separated into JSON files, making it simple to update without touching the code.

## 📁 Configuration Files

### `src/config/site.json`
Contains global site information:
- Site title, description, author
- Social media links (GitHub, email, LinkedIn, website)
- Hero section content (title, subtitle, description, button text)
- Navigation menu items

### `src/config/sections.json`
Contains content for main sections:
- **Video Showcase**: YouTube video ID, titles, descriptions
- **Live Demo**: Demo URLs, download links, control instructions
- **What I Built**: Problem statement, technology list
- **Try It Yourself**: GitHub links, quick start commands

### `src/config/features.json`
Contains the feature list with:
- Icon names (from Lucide React icon library)
- Feature titles and descriptions

### `src/config/designDecisions.json`
Contains the technical decision tabs:
- Tab titles and content
- Code examples
- Benefits/tradeoffs lists
- Performance notes

## 🎨 How to Customize

### 1. Basic Information
Edit `src/config/site.json`:
```json
{
  "site": {
    "title": "Your Portfolio Title",
    "author": "Your Name"
  },
  "social": {
    "github": "https://github.com/yourusername",
    "email": "your@email.com"
  }
}
```

### 2. Hero Section
Update the hero content in `src/config/site.json`:
```json
{
  "hero": {
    "title": "Your Project Title",
    "subtitle": "by Your Name",
    "description": "Your project description..."
  }
}
```

### 3. Video Showcase
Change the YouTube video in `src/config/sections.json`:
```json
{
  "videoShowcase": {
    "youtubeVideoId": "YOUR_VIDEO_ID"
  }
}
```

### 4. Features
Add/edit features in `src/config/features.json`:
```json
{
  "features": [
    {
      "icon": "Zap",
      "title": "Your Feature",
      "description": "Feature description..."
    }
  ]
}
```

Available icons: Any icon from [Lucide React](https://lucide.dev/icons/)

### 5. Technologies
Update the tech stack in `src/config/sections.json`:
```json
{
  "whatIBuilt": {
    "technologies": ["React", "TypeScript", "Your Tech"]
  }
}
```

### 6. GitHub Links
Update all GitHub-related URLs in `src/config/sections.json`:
```json
{
  "tryItYourself": {
    "githubRepo": "https://github.com/yourusername/yourproject",
    "releasesUrl": "https://github.com/yourusername/yourproject/releases"
  }
}
```

## 🔧 Advanced Customization

### Adding New Sections
1. Add section content to appropriate config file
2. Create a new component in `src/components/`
3. Import the component in `src/pages/Index.tsx`
4. Add navigation link in `src/config/site.json`

### Styling Changes
- Colors are defined in `src/index.css` as CSS variables
- Main theme colors: `--engine-blue` and `--engine-red`
- Tailwind classes are used throughout for consistent styling

### Icon Changes
- All icons use Lucide React
- Change icon names in config files (must match Lucide icon names)
- Icons are automatically imported and rendered

## 📱 Responsive Design
The theme is fully responsive and works on:
- Desktop computers
- Tablets
- Mobile phones

No additional configuration needed for responsiveness.

## 🚀 Deployment
The theme works with:
- GitHub Pages
- Netlify
- Vercel
- Any static hosting service

## 💡 Tips
1. Always use valid JSON syntax in config files
2. Preview changes locally before deploying
3. Keep descriptions concise for better mobile experience
4. Use high-quality images and videos for best results
5. Test all external links before publishing

## 🆘 Common Issues
- **JSON syntax errors**: Use a JSON validator if the site breaks
- **Missing icons**: Check Lucide React documentation for valid icon names
- **Broken links**: Verify all URLs in config files are accessible
