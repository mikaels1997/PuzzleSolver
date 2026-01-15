import './App.css';
import ReactDOM from "react-dom/client";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Layout from "./pages/Layout";
import Home from "./pages/Home";
import SudokuPage from "./pages/SudokuPage";
import NoPage from "./pages/NoPage";
import WordFinderPage from 'pages/WordFinderPage';


function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Layout />}>
          <Route index element={<Home />} />
          <Route path="sudoku" element={<SudokuPage />} />
          <Route path="word-finder" element={<WordFinderPage />} />
          <Route path="*" element={<NoPage />} />
        </Route>
      </Routes>
    </BrowserRouter>
  );
}

export default App;
