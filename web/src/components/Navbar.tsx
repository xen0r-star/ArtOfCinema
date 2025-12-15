import { Link, useLocation } from 'react-router-dom';
import { Film, Download, Home, Book } from 'lucide-react';
import { clsx } from 'clsx';

const Navbar = () => {
    const location = useLocation();

    const links = [
        { name: 'Accueil', path: '/', icon: Home },
        { name: 'Versions', path: '/releases', icon: Download },
        { name: 'Documentation', path: '/docs', icon: Book }
    ];

    return (
        <nav className="bg-surface border-b border-white/10 sticky top-0 z-50 backdrop-blur-md bg-opacity-80">
            <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
                <div className="flex items-center justify-between h-16">
                    <div className="flex items-center gap-2">
                        <Film className="h-8 w-8 text-primary" />
                        <span className="text-xl font-bold tracking-wider">ArtOfCinema</span>
                    </div>

                    <div className="hidden md:block">
                        <div className="ml-10 flex items-baseline space-x-4">
                            {links.map((link) => {
                                const Icon = link.icon;
                                const isActive = location.pathname === link.path;
                                return (
                                    <Link
                                        key={link.name}
                                        to={link.path}
                                        className={clsx(
                                            'flex items-center gap-2 px-3 py-2 rounded-md text-sm font-medium transition-colors',
                                            isActive
                                                ? 'bg-primary text-white'
                                                : 'text-gray-300 hover:bg-white/10 hover:text-white'
                                        )}
                                    >
                                        <Icon className="w-4 h-4" />
                                        {link.name}
                                    </Link>
                                );
                            })}
                        </div>
                    </div>
                </div>
            </div>
        </nav>
    );
};

export default Navbar;
