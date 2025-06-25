
import React, { useState } from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Textarea } from '@/components/ui/textarea';
import { Github, Mail, Linkedin } from 'lucide-react';

const Contact = () => {
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    message: ''
  });

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    // Handle form submission - replace with actual implementation
    console.log('Form submitted:', formData);
    alert('Message sent! (This is a demo - implement with your preferred method)');
    setFormData({ name: '', email: '', message: '' });
  };

  const handleChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  return (
    <section className="py-20 bg-gray-950">
      <div className="container mx-auto px-6">
        <div className="text-center mb-12">
          <h2 className="text-4xl md:text-5xl font-bold text-white mb-4 animate-fade-in-up">
            Get In <span className="text-blue-500">Touch</span>
          </h2>
          <p className="text-xl text-gray-400 animate-fade-in-up" style={{ animationDelay: '0.2s' }}>
            Let's discuss game development, engine architecture, or potential collaborations
          </p>
        </div>
        
        <div className="max-w-4xl mx-auto">
          <div className="grid md:grid-cols-2 gap-8">
            <div className="space-y-6">
              <div className="animate-fade-in-up" style={{ animationDelay: '0.3s' }}>
                <h3 className="text-2xl font-bold text-white mb-6">Connect With Me</h3>
                <div className="space-y-4">
                  <a 
                    href="mailto:your.email@example.com"
                    className="flex items-center gap-4 p-4 bg-card border border-border rounded-lg hover:bg-gray-800/50 transition-colors group"
                  >
                    <Mail className="w-6 h-6 text-red-500 group-hover:scale-110 transition-transform" />
                    <div>
                      <div className="text-white font-medium">Email</div>
                      <div className="text-gray-400 text-sm">your.email@example.com</div>
                    </div>
                  </a>
                  
                  <a 
                    href="https://github.com/nithilan"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="flex items-center gap-4 p-4 bg-card border border-border rounded-lg hover:bg-gray-800/50 transition-colors group"
                  >
                    <Github className="w-6 h-6 text-blue-500 group-hover:scale-110 transition-transform" />
                    <div>
                      <div className="text-white font-medium">GitHub</div>
                      <div className="text-gray-400 text-sm">github.com/nithilan</div>
                    </div>
                  </a>
                  
                  <a 
                    href="https://linkedin.com/in/nithilan"
                    target="_blank"
                    rel="noopener noreferrer"
                    className="flex items-center gap-4 p-4 bg-card border border-border rounded-lg hover:bg-gray-800/50 transition-colors group"
                  >
                    <Linkedin className="w-6 h-6 text-red-500 group-hover:scale-110 transition-transform" />
                    <div>
                      <div className="text-white font-medium">LinkedIn</div>
                      <div className="text-gray-400 text-sm">linkedin.com/in/nithilan</div>
                    </div>
                  </a>
                </div>
              </div>
            </div>
            
            <Card className="bg-card border-border animate-fade-in-up" style={{ animationDelay: '0.4s' }}>
              <CardHeader>
                <CardTitle className="text-white text-xl">Send a Message</CardTitle>
              </CardHeader>
              <CardContent>
                <form onSubmit={handleSubmit} className="space-y-4">
                  <div>
                    <Input
                      type="text"
                      name="name"
                      placeholder="Your Name"
                      value={formData.name}
                      onChange={handleChange}
                      required
                      className="bg-gray-900 border-gray-700 text-white placeholder-gray-400"
                    />
                  </div>
                  <div>
                    <Input
                      type="email"
                      name="email"
                      placeholder="Your Email"
                      value={formData.email}
                      onChange={handleChange}
                      required
                      className="bg-gray-900 border-gray-700 text-white placeholder-gray-400"
                    />
                  </div>
                  <div>
                    <Textarea
                      name="message"
                      placeholder="Your Message"
                      value={formData.message}
                      onChange={handleChange}
                      required
                      rows={4}
                      className="bg-gray-900 border-gray-700 text-white placeholder-gray-400"
                    />
                  </div>
                  <Button 
                    type="submit" 
                    className="w-full bg-blue-600 hover:bg-blue-700 text-white"
                  >
                    Send Message
                  </Button>
                </form>
              </CardContent>
            </Card>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Contact;
