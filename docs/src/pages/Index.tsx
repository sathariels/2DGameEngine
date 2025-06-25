
import { useEffect } from 'react';
import Header from '@/components/Header';
import HeroSection from '@/components/HeroSection';
import VideoShowcase from '@/components/VideoShowcase';
import LiveDemo from '@/components/LiveDemo';
import WhatIBuilt from '@/components/WhatIBuilt';
import DesignDecisions from '@/components/DesignDecisions';
import TryItYourself from '@/components/TryItYourself';
import Contact from '@/components/Contact';
import Footer from '@/components/Footer';

const Index = () => {
  useEffect(() => {
    // Scroll animation observer
    const observer = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            entry.target.classList.add('visible');
          }
        });
      },
      { threshold: 0.1 }
    );

    // Observe all elements with animate-on-scroll class
    const elements = document.querySelectorAll('.animate-on-scroll');
    elements.forEach((el) => observer.observe(el));

    return () => observer.disconnect();
  }, []);

  return (
    <div className="min-h-screen bg-background">
      <Header />
      <main>
        <HeroSection />
        <VideoShowcase />
        <LiveDemo />
        <WhatIBuilt />
        <DesignDecisions />
        <TryItYourself />
        <Contact />
      </main>
      <Footer />
    </div>
  );
};

export default Index;
