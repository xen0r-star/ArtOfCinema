import { ArrowRight, Terminal, Shield, Zap } from 'lucide-react';
import { Link } from 'react-router-dom';

const Home = () => {
    return (
        <div className="relative overflow-hidden">
            {/* Hero Section */}
            <div className="relative pt-16 pb-32 flex content-center items-center justify-center min-h-[75vh]">
                <div className="absolute top-0 w-full h-full bg-center bg-cover opacity-20" style={{ backgroundImage: 'url("https://images.unsplash.com/photo-1489599849927-2ee91cede3ba?q=80&w=2070&auto=format&fit=crop")' }}></div>
                <div className="container relative mx-auto">
                    <div className="items-center flex flex-wrap">
                        <div className="w-full lg:w-6/12 px-4 ml-auto mr-auto text-center">
                            <div className="pr-12">
                                <h1 className="text-white font-semibold text-5xl">
                                    Gérez votre cinéma avec <span className="text-primary">ArtOfCinema</span>
                                </h1>
                                <p className="mt-4 text-lg text-gray-300">
                                    Une solution puissante, rapide et sécurisée écrite en C pour la gestion complète de vos salles, films et clients.
                                </p>
                                <div className="mt-8 flex justify-center gap-4">
                                    <Link to="/releases" className="bg-primary hover:bg-rose-700 text-white font-bold py-3 px-6 rounded-lg transition-colors flex items-center gap-2">
                                        Télécharger la v1.0 <ArrowRight className="w-4 h-4" />
                                    </Link>
                                    <Link to="/docs" className="bg-white/10 hover:bg-white/20 text-white font-bold py-3 px-6 rounded-lg transition-colors backdrop-blur-sm">
                                        Documentation
                                    </Link>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

            {/* Features Section */}
            <section className="pb-20 bg-surface -mt-24 pt-20 rounded-t-3xl relative z-10">
                <div className="container mx-auto px-4">
                    <div className="flex flex-wrap">
                        <div className="lg:pt-12 pt-6 w-full md:w-4/12 px-4 text-center">
                            <div className="min-h-[300px] relative flex flex-col min-w-0 bg-background w-full mb-8 shadow-lg rounded-lg p-8 border border-white/5 hover:border-primary/50 transition-colors">
                                <div className="px-4 py-5 flex-auto">
                                    <div className="text-white p-3 text-center inline-flex items-center justify-center w-12 h-12 mb-5 shadow-lg rounded-full bg-primary">
                                        <Zap className="w-6 h-6" />
                                    </div>
                                    <h6 className="text-xl font-semibold">Performance Maximale</h6>
                                    <p className="mt-2 mb-4 text-gray-400">
                                        Écrit en C pur pour une rapidité d'exécution inégalée et une empreinte mémoire minimale.
                                    </p>
                                </div>
                            </div>
                        </div>

                        <div className="w-full md:w-4/12 px-4 text-center">
                            <div className="min-h-[300px] relative flex flex-col min-w-0 bg-background w-full mb-8 shadow-lg rounded-lg p-8 border border-white/5 hover:border-primary/50 transition-colors">
                                <div className="px-4 py-5 flex-auto">
                                    <div className="text-white p-3 text-center inline-flex items-center justify-center w-12 h-12 mb-5 shadow-lg rounded-full bg-blue-600">
                                        <Terminal className="w-6 h-6" />
                                    </div>
                                    <h6 className="text-xl font-semibold">Interface CLI Intuitive</h6>
                                    <p className="mt-2 mb-4 text-gray-400">
                                        Une interface robuste et facile à utiliser.
                                    </p>
                                </div>
                            </div>
                        </div>

                        <div className="lg:pt-12 pt-6 w-full md:w-4/12 px-4 text-center">
                            <div className="min-h-[300px] relative flex flex-col min-w-0 bg-background w-full mb-8 shadow-lg rounded-lg p-8 border border-white/5 hover:border-primary/50 transition-colors">
                                <div className="px-4 py-5 flex-auto">
                                    <div className="text-white p-3 text-center inline-flex items-center justify-center w-12 h-12 mb-5 shadow-lg rounded-full bg-emerald-600">
                                        <Shield className="w-6 h-6" />
                                    </div>
                                    <h6 className="text-xl font-semibold">Sécurité Renforcée</h6>
                                    <p className="mt-2 mb-4 text-gray-400">
                                        Gestion des utilisateurs et des permissions intégrée pour protéger vos données sensibles.
                                    </p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </section>
        </div>
    );
};

export default Home;
