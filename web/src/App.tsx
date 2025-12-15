import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import Layout from './components/Layout';
import Home from './pages/Home';
import Releases from './pages/Releases';

function App() {
  return (
    <Router>
      <Layout>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/releases" element={<Releases />} />
          <Route path="/docs" element={<div className="p-20 text-center text-2xl">Documentation en cours de rédaction...</div>} />
        </Routes>
      </Layout>
    </Router>
  );
}

export default App;
