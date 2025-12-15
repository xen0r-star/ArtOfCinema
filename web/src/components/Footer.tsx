import { Github } from 'lucide-react';

const Footer = () => {
    return (
        <footer className="bg-surface border-t border-white/10 py-8 mt-auto">
            <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
                <div className="flex flex-col md:flex-row justify-between items-center gap-4">
                    <div className="text-gray-400 text-sm">
                        © {new Date().getFullYear()} ArtOfCinema. Tous droits réservés.
                    </div>

                    <div className="flex space-x-6">
                        <a href="https://github.com/xen0r-star/ArtOfCinema" className="text-gray-400 hover:text-white transition-colors">
                            <Github className="h-5 w-5" />
                        </a>
                    </div>
                </div>
            </div>
        </footer>
    );
};

export default Footer;
