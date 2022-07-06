import App from './App';
import DevelopmentProcess from './routes/DevelopmentProcess';
import Docs from './routes/Docs';
import Home from './routes/Home';
import React from 'react';
import ReactDOM from 'react-dom';
import { BrowserRouter, Routes, Route } from 'react-router-dom';

ReactDOM.render(
  <BrowserRouter>
    <Routes>
      <Route path="/" element={<App />}>
        <Route path="Docs" element={<Docs />} />
        <Route path="Home" element={<Home />} />
        <Route path="Development-Process" element={<DevelopmentProcess />} />
      </Route>
      <Route />
    </Routes>
  </BrowserRouter>,
  document.getElementById('root')
);
