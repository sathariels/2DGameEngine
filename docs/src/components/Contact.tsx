
import { Mail, Github, Linkedin, ExternalLink } from 'lucide-react';

const Contact = () => {
  return (
    <section id="contact" className="py-20 bg-black">
      <div className="max-w-4xl mx-auto px-4 sm:px-6 lg:px-8">
        <div className="text-center mb-16">
          <h2 className="text-4xl sm:text-5xl font-bold text-white mb-6">
            Get In <span className="text-blue-400">Touch</span>
          </h2>
          <p className="text-xl text-gray-300 max-w-3xl mx-auto">
            Interested in game development, engine architecture, or potential collaboration? I'd love to hear from you.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-3 gap-8 mb-12">
          <a 
            href="mailto:contact@nithilan.dev"
            className="group bg-gray-900 border border-gray-700 rounded-xl p-6 text-center hover:border-blue-500/50 transition-all duration-300 hover:transform hover:scale-105"
          >
            <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4 group-hover:bg-blue-500/30 transition-colors">
              <Mail className="w-8 h-8 text-blue-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-2 group-hover:text-blue-400 transition-colors">Email</h3>
            <p className="text-gray-300">contact@nithilan.dev</p>
          </a>

          <a 
            href="https://github.com/nithilan"
            target="_blank"
            rel="noopener noreferrer"
            className="group bg-gray-900 border border-gray-700 rounded-xl p-6 text-center hover:border-blue-500/50 transition-all duration-300 hover:transform hover:scale-105"
          >
            <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4 group-hover:bg-blue-500/30 transition-colors">
              <Github className="w-8 h-8 text-blue-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-2 group-hover:text-blue-400 transition-colors">GitHub</h3>
            <p className="text-gray-300">@nithilan</p>
          </a>

          <a 
            href="https://linkedin.com/in/nithilan"
            target="_blank"
            rel="noopener noreferrer"
            className="group bg-gray-900 border border-gray-700 rounded-xl p-6 text-center hover:border-blue-500/50 transition-all duration-300 hover:transform hover:scale-105"
          >
            <div className="w-16 h-16 bg-blue-500/20 rounded-full flex items-center justify-center mx-auto mb-4 group-hover:bg-blue-500/30 transition-colors">
              <Linkedin className="w-8 h-8 text-blue-400" />
            </div>
            <h3 className="text-xl font-bold text-white mb-2 group-hover:text-blue-400 transition-colors">LinkedIn</h3>
            <p className="text-gray-300">Connect with me</p>
          </a>
        </div>

        <div className="bg-gray-900 border border-gray-700 rounded-2xl p-8">
          <div className="flex items-center justify-between flex-wrap gap-4">
            <div>
              <h3 className="text-2xl font-bold text-white mb-2">Want to learn more?</h3>
              <p className="text-gray-300">Visit my main website for more projects and insights into my work.</p>
            </div>
            <a 
              href="https://nithilan.dev"
              target="_blank"
              rel="noopener noreferrer"
              className="group flex items-center space-x-2 bg-red-500 hover:bg-red-600 text-white px-6 py-3 rounded-lg font-medium transition-all duration-300 hover:transform hover:scale-105"
            >
              <span>Visit nithilan.dev</span>
              <ExternalLink className="w-4 h-4 group-hover:translate-x-1 transition-transform" />
            </a>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Contact;
