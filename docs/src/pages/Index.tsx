
import Navbar from '@/components/Navbar';
import HeroSection from '@/components/HeroSection';
import VideoShowcase from '@/components/VideoShowcase';
import LiveDemo from '@/components/LiveDemo';
import WhatIBuilt from '@/components/WhatIBuilt';
import DesignDecisions from '@/components/DesignDecisions';
import TryItYourself from '@/components/TryItYourself';
import Contact from '@/components/Contact';
import Footer from '@/components/Footer';

const Index = () => {
  return (
    <div className="min-h-screen bg-black">
      <Navbar />
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
