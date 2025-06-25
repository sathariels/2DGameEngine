
import React, { useEffect } from 'react';
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
    // Smooth scrolling for anchor links
    const handleSmoothScroll = (e: Event) => {
      const target = e.target as HTMLElement;
      if (target.tagName === 'A' && target.getAttribute('href')?.startsWith('#')) {
        e.preventDefault();
        const id = target.getAttribute('href')?.substring(1);
        const element = document.getElementById(id || '');
        element?.scrollIntoView({ behavior: 'smooth' });
      }
    };

    document.addEventListener('click', handleSmoothScroll);
    return () => document.removeEventListener('click', handleSmoothScroll);
  }, []);

  return (
    <div className="min-h-screen bg-black text-white">
      <Header />
      <HeroSection />
      <VideoShowcase />
      <LiveDemo />
      <WhatIBuilt />
      <DesignDecisions />
      <TryItYourself />
      <Contact />
      <Footer />
    </div>
  );
};

export default Index;
