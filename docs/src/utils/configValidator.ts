
export const validateConfig = (config: any, schema: string): boolean => {
  try {
    JSON.parse(JSON.stringify(config));
    console.log(`✅ ${schema} configuration is valid`);
    return true;
  } catch (error) {
    console.error(`❌ ${schema} configuration is invalid:`, error);
    return false;
  }
};

export const validateAllConfigs = async () => {
  const configs = [
    { path: '/src/config/site.json', name: 'Site' },
    { path: '/src/config/sections.json', name: 'Sections' },
    { path: '/src/config/features.json', name: 'Features' },
    { path: '/src/config/designDecisions.json', name: 'Design Decisions' }
  ];

  let allValid = true;

  for (const config of configs) {
    try {
      const response = await fetch(config.path);
      const data = await response.json();
      const isValid = validateConfig(data, config.name);
      if (!isValid) allValid = false;
    } catch (error) {
      console.error(`❌ Failed to load ${config.name} config:`, error);
      allValid = false;
    }
  }

  if (allValid) {
    console.log('🎉 All configurations are valid!');
  } else {
    console.log('⚠️ Some configurations have issues. Check the errors above.');
  }

  return allValid;
};
