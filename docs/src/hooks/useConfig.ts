
import { useState, useEffect } from 'react';

export interface SiteConfig {
  site: {
    title: string;
    description: string;
    author: string;
    url: string;
    keywords: string;
  };
  social: {
    github: string;
    email: string;
    linkedin: string;
    website: string;
  };
  hero: {
    title: string;
    subtitle: string;
    description: string;
    primaryButton: {
      text: string;
      action: string;
    };
    secondaryButton: {
      text: string;
      action: string;
    };
  };
  navigation: {
    logo: string;
    items: Array<{
      name: string;
      href: string;
    }>;
  };
}

export interface SectionsConfig {
  videoShowcase: {
    title: string;
    description: string;
    youtubeVideoId: string;
    additionalInfo: string;
  };
  liveDemo: {
    title: string;
    description: string;
    cardTitle: string;
    demoUrl: string;
    downloadUrl: string;
    downloadFilename: string;
    controls: string[];
  };
  whatIBuilt: {
    title: string;
    description: string;
    problemStatement: string;
    technologies: string[];
  };
  tryItYourself: {
    title: string;
    description: string;
    githubRepo: string;
    releasesUrl: string;
    docsUrl: string;
    setupGuideUrl: string;
    quickStart: {
      commands: string[];
    };
  };
}

export interface Feature {
  icon: string;
  title: string;
  description: string;
}

export interface FeaturesConfig {
  features: Feature[];
}

export interface DesignDecisionsConfig {
  title: string;
  description: string;
  tabs: Array<{
    id: string;
    title: string;
    content: {
      title: string;
      description: string;
      codeExample?: string;
      benefits?: string[];
      tradeoffs?: string[];
      performanceNote?: string;
      whyLua?: string;
    };
  }>;
}

export const useConfig = () => {
  const [siteConfig, setSiteConfig] = useState<SiteConfig | null>(null);
  const [sectionsConfig, setSectionsConfig] = useState<SectionsConfig | null>(null);
  const [featuresConfig, setFeaturesConfig] = useState<FeaturesConfig | null>(null);
  const [designDecisionsConfig, setDesignDecisionsConfig] = useState<DesignDecisionsConfig | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const loadConfigs = async () => {
      try {
        const [siteResponse, sectionsResponse, featuresResponse, designResponse] = await Promise.all([
          fetch('/src/config/site.json'),
          fetch('/src/config/sections.json'),
          fetch('/src/config/features.json'),
          fetch('/src/config/designDecisions.json')
        ]);

        const [site, sections, features, design] = await Promise.all([
          siteResponse.json(),
          sectionsResponse.json(),
          featuresResponse.json(),
          designResponse.json()
        ]);

        setSiteConfig(site);
        setSectionsConfig(sections);
        setFeaturesConfig(features);
        setDesignDecisionsConfig(design);
      } catch (error) {
        console.error('Error loading configuration:', error);
      } finally {
        setLoading(false);
      }
    };

    loadConfigs();
  }, []);

  return {
    siteConfig,
    sectionsConfig,
    featuresConfig,
    designDecisionsConfig,
    loading
  };
};
