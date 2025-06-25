
import { Card, CardContent } from '@/components/ui/card';
import { Github, Mail, Linkedin, ExternalLink } from 'lucide-react';

const Contact = () => {
  return (
    <section className="py-20 bg-background">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12 animate-fade-in-up">
          <h2 className="text-4xl font-bold mb-4 text-gradient">Get In Touch</h2>
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
            Interested in collaborating, have questions about the engine, 
            or want to discuss game development? I'd love to hear from you.
          </p>
        </div>
        
        <div className="max-w-2xl mx-auto animate-fade-in">
          {/* Contact Links */}
          <div className="space-y-6">
            <Card className="hover:shadow-lg transition-all duration-300 border-l-4 border-l-engine-blue group">
              <CardContent className="p-6">
                <div className="flex items-center space-x-4">
                  <div className="p-3 bg-engine-blue/10 rounded-lg group-hover:bg-engine-blue/20 transition-colors duration-300">
                    <Mail className="h-6 w-6 text-engine-blue" />
                  </div>
                  <div>
                    <h3 className="text-lg font-semibold">Email</h3>
                    <a 
                      href="mailto:nithilan@example.com" 
                      className="text-muted-foreground hover:text-engine-blue transition-colors duration-200"
                    >
                      nithilan@example.com
                    </a>
                  </div>
                </div>
              </CardContent>
            </Card>
            
            <Card className="hover:shadow-lg transition-all duration-300 border-l-4 border-l-engine-red group">
              <CardContent className="p-6">
                <div className="flex items-center space-x-4">
                  <div className="p-3 bg-engine-red/10 rounded-lg group-hover:bg-engine-red/20 transition-colors duration-300">
                    <Github className="h-6 w-6 text-engine-red" />
                  </div>
                  <div>
                    <h3 className="text-lg font-semibold">GitHub</h3>
                    <a 
                      href="https://github.com/yourusername" 
                      target="_blank"
                      rel="noopener noreferrer"
                      className="text-muted-foreground hover:text-engine-red transition-colors duration-200 flex items-center gap-1"
                    >
                      @yourusername
                      <ExternalLink className="h-3 w-3" />
                    </a>
                  </div>
                </div>
              </CardContent>
            </Card>
            
            <Card className="hover:shadow-lg transition-all duration-300 border-l-4 border-l-engine-blue group">
              <CardContent className="p-6">
                <div className="flex items-center space-x-4">
                  <div className="p-3 bg-engine-blue/10 rounded-lg group-hover:bg-engine-blue/20 transition-colors duration-300">
                    <Linkedin className="h-6 w-6 text-engine-blue" />
                  </div>
                  <div>
                    <h3 className="text-lg font-semibold">LinkedIn</h3>
                    <a 
                      href="https://linkedin.com/in/yourprofile" 
                      target="_blank"
                      rel="noopener noreferrer"
                      className="text-muted-foreground hover:text-engine-blue transition-colors duration-200 flex items-center gap-1"
                    >
                      /in/yourprofile
                      <ExternalLink className="h-3 w-3" />
                    </a>
                  </div>
                </div>
              </CardContent>
            </Card>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Contact;
