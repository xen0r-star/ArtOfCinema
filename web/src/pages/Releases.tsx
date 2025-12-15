import { useEffect, useState } from 'react';
import { Download, Calendar, Tag, CheckCircle, Loader2, AlertCircle } from 'lucide-react';

interface Release {
    version: string;
    date: string;
    description: string;
    features: string[];
    downloadUrl: string;
    sourceUrl: string;
    isLatest?: boolean;
}

interface GitHubAsset {
    name: string;
    browser_download_url: string;
}

interface GitHubRelease {
    tag_name: string;
    published_at: string;
    body: string;
    html_url: string;
    assets: GitHubAsset[];
}

const Releases = () => {
    const [releases, setReleases] = useState<Release[]>([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState<string | null>(null);

    useEffect(() => {
        const fetchReleases = async () => {
            try {
                const response = await fetch('https://api.github.com/repos/LaurieWired/GhidraMCP/releases');
                // const response = await fetch('https://api.github.com/repos/xen0r-star/ArtOfCinema/releases');
                if (!response.ok) {
                    throw new Error('Impossible de récupérer les versions depuis GitHub');
                }
                
                const data: GitHubRelease[] = await response.json();
                
                const formattedReleases = data.map((release: GitHubRelease, index: number) => {
                    // Tentative d'extraction des fonctionnalités depuis le markdown (lignes commençant par - ou *)
                    const bodyLines = release.body ? release.body.split('\n') : [];
                    const features = bodyLines
                        .filter((line: string) => line.trim().startsWith('- ') || line.trim().startsWith('* '))
                        .map((line: string) => line.trim().substring(2).trim());
                    
                    // Le reste du texte est considéré comme description
                    const descriptionLines = bodyLines
                        .filter((line: string) => !line.trim().startsWith('- ') && !line.trim().startsWith('* ') && !line.trim().startsWith('#'))
                        .filter((line: string) => line.trim() !== '');
                    
                    const description = descriptionLines.join(' ');

                    // Chercher un asset .zip ou .exe, sinon lien par défaut
                    const asset = release.assets.find((a: GitHubAsset) => a.name.endsWith('.zip') || a.name.endsWith('.exe'));

                    return {
                        version: release.tag_name,
                        date: new Date(release.published_at).toLocaleDateString('fr-FR', { 
                            year: 'numeric', 
                            month: 'long', 
                            day: 'numeric' 
                        }),
                        description: description || "Voir les détails sur GitHub.",
                        features: features,
                        downloadUrl: asset ? asset.browser_download_url : release.html_url,
                        sourceUrl: release.html_url,
                        isLatest: index === 0
                    };
                });

                setReleases(formattedReleases);
            } catch (err) {
                setError("Impossible de charger les versions depuis GitHub.");
                console.error(err);
            } finally {
                setLoading(false);
            }
        };

        fetchReleases();
    }, []);

    return (
        <div className="container mx-auto px-4 py-12">
            <div className="text-center mb-16">
                <h1 className="text-4xl font-bold mb-4">Versions & Téléchargements</h1>
                <p className="text-gray-400 max-w-2xl mx-auto">
                    Retrouvez ici toutes les versions de ArtOfCinema. Nous recommandons toujours d'utiliser la dernière version stable.
                </p>
            </div>

            {loading ? (
                <div className="flex justify-center py-20">
                    <Loader2 className="w-10 h-10 animate-spin text-primary" />
                </div>
            ) : error ? (
                <div className="flex flex-col items-center justify-center py-20 text-red-400">
                    <AlertCircle className="w-10 h-10 mb-4" />
                    <p>{error}</p>
                </div>
            ) : releases.length === 0 ? (
                <div className="text-center text-gray-500 py-20">
                    Aucune version disponible pour le moment.
                </div>
            ) : (
                <div className="max-w-4xl mx-auto space-y-8">
                    {releases.map((release) => (
                        <div key={release.version} className="bg-surface border border-white/10 rounded-xl overflow-hidden hover:border-primary/30 transition-colors">
                            <div className="p-6 md:p-8">
                                <div className="flex flex-col md:flex-row md:items-center justify-between gap-4 mb-6">
                                    <div className="flex items-center gap-4">
                                        <h2 className="text-2xl font-bold text-white">{release.version}</h2>
                                        {release.isLatest && (
                                            <span className="bg-primary/20 text-primary text-xs font-bold px-3 py-1 rounded-full border border-primary/20">
                                                LATEST
                                            </span>
                                        )}
                                    </div>
                                    <div className="flex items-center gap-2 text-gray-400 text-sm">
                                        <Calendar className="w-4 h-4" />
                                        {release.date}
                                    </div>
                                </div>

                                <p className="text-gray-300 mb-6">{release.description}</p>

                                {release.features.length > 0 && (
                                    <div className="mb-8">
                                        <h3 className="text-sm font-semibold text-gray-400 uppercase tracking-wider mb-4">Nouveautés</h3>
                                        <ul className="grid md:grid-cols-2 gap-3">
                                            {release.features.map((feature, idx) => (
                                                <li key={idx} className="flex items-start gap-2 text-gray-300">
                                                    <CheckCircle className="w-5 h-5 text-green-500 shrink-0" />
                                                    <span>{feature}</span>
                                                </li>
                                            ))}
                                        </ul>
                                    </div>
                                )}

                                <div className="flex flex-col sm:flex-row gap-4 pt-6 border-t border-white/5">
                                    <a
                                        href={release.downloadUrl}
                                        className="flex items-center justify-center gap-2 bg-white text-black hover:bg-gray-200 font-bold py-3 px-6 rounded-lg transition-colors"
                                    >
                                        <Download className="w-4 h-4" />
                                        Télécharger {release.version}
                                    </a>
                                    <a
                                        href={release.sourceUrl}
                                        target="_blank"
                                        rel="noopener noreferrer"
                                        className="flex items-center justify-center gap-2 bg-surface border border-white/20 hover:bg-white/5 text-white font-semibold py-3 px-6 rounded-lg transition-colors"
                                    >
                                        <Tag className="w-4 h-4" />
                                        Code Source
                                    </a>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            )}
        </div>
    );
};

export default Releases;
