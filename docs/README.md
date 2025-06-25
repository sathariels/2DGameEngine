
# Nithilan's 2D Game Engine Portfolio

A modern, interactive portfolio website showcasing a custom 2D game engine built with React, TypeScript, and Tailwind CSS.

## 🚀 Features

- **Modern Design**: Clean, techy aesthetic with smooth animations
- **Responsive**: Optimized for desktop and mobile devices
- **Interactive**: Engaging user experience with scroll animations
- **GitHub Pages Ready**: Configured for easy deployment to GitHub Pages
- **YouTube Integration**: Seamless video embedding for demos
- **Easy Asset Management**: Organized folder structure for media files

## 📁 Project Structure

```
src/
├── components/          # React components
│   ├── Header.tsx      # Navigation header
│   ├── HeroSection.tsx # Landing section with video background
│   ├── VideoShowcase.tsx # Main demo video section
│   ├── LiveDemo.tsx    # Interactive demo embedding
│   ├── WhatIBuilt.tsx  # Technical overview
│   ├── DesignDecisions.tsx # Architecture explanations
│   ├── TryItYourself.tsx # Download/GitHub links
│   ├── Contact.tsx     # Contact form and social links
│   └── Footer.tsx      # Site footer
├── pages/
│   └── Index.tsx       # Main page layout
└── styles/             # CSS and styling

public/assets/
├── videos/             # Video files and YouTube integration
├── images/             # Screenshots, diagrams, and graphics
└── demo/               # Interactive demo files
```

## 🎨 Color Scheme

- **Primary**: Black (#000000) and White (#FFFFFF)
- **Accents**: Red (#DC2626) and Blue (#2563EB)
- **Theme**: Modern, high-contrast design for technical content

## 🔧 Customization

### Adding Your Videos
1. **YouTube Method** (Recommended):
   - Upload videos to YouTube
   - Copy video IDs and update in components
   - Replace `dQw4w9WgXcQ` with your video ID

2. **Local Files Method**:
   - Place video files in `public/assets/videos/`
   - Update components to use HTML5 video elements

### Updating Content
- **Personal Info**: Update links in `Header.tsx` and `Contact.tsx`
- **Technical Details**: Modify content in `WhatIBuilt.tsx` and `DesignDecisions.tsx`
- **GitHub Links**: Update repository URLs in `TryItYourself.tsx`

### Adding Interactive Demo
1. Place demo files in `public/assets/demo/`
2. Update the iframe/embed code in `LiveDemo.tsx`
3. For WebAssembly demos, include .wasm and .js files

## 🚀 Deployment to GitHub Pages

1. **Enable GitHub Pages**:
   - Go to your repository settings
   - Navigate to "Pages" section
   - Select "GitHub Actions" as source

2. **Configure for GitHub Pages**:
   - The site is already configured with proper base paths
   - Assets will be served from the correct URLs

3. **Auto-deployment**:
   - Push changes to main branch
   - GitHub Actions will build and deploy automatically

## 📱 Responsive Design

The website is fully responsive with:
- Mobile-first design approach
- Fluid typography and spacing
- Touch-friendly interactive elements
- Optimized images and videos for all screen sizes

## ⚡ Performance Features

- **Lazy Loading**: Images and videos load as needed
- **Optimized Assets**: Compressed images and efficient video formats
- **Smooth Animations**: CSS-based animations for better performance
- **Fast Loading**: Optimized bundle size and code splitting

## 🛠 Development

```bash
# Install dependencies
npm install

# Start development server
npm run dev

# Build for production
npm run build

# Preview production build
npm run preview
```

## 📧 Contact Integration

The contact form is currently set up as a demo. To make it functional:

1. **Email Integration**: Use EmailJS, Formspree, or Netlify Forms
2. **Backend Service**: Set up your own API endpoint
3. **Static Form**: Use a service like Formsubmit.co

## 🎯 SEO & Meta Tags

- Proper meta descriptions and titles
- Open Graph tags for social sharing
- Twitter Card support
- Structured data for better search indexing

---

Built with ❤️ using React, TypeScript, and Tailwind CSS
