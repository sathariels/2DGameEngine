
import { Navigation } from '@/components/Navigation';
import { HeroSection } from '@/components/HeroSection';
import { FeaturesSection } from '@/components/FeaturesSection';
import { DemoSection } from '@/components/DemoSection';
import { DesignSection } from '@/components/DesignSection';
import { TryItSection } from '@/components/TryItSection';
import { Footer } from '@/components/Footer';

const Index = () => {
  return (
    <div className="min-h-screen bg-background">
      <Navigation />
      <HeroSection />
      <FeaturesSection />
      <DemoSection />
      <DesignSection />
      <TryItSection />
      <Footer />
    </div>
  );
};

export default Index;
