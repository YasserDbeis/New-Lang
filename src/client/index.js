import App from './App';
import Docs from './routes/Docs';
import Home from './routes/Home';
import React from 'react';
import ReactDOM from 'react-dom';
import {
  BrowserRouter,
  Routes,
  Route,
  Redirect,
  Navigate,
} from 'react-router-dom';

ReactDOM.render(
  <BrowserRouter>
    <Routes>
      <Route path="/" element={<App />}>
        <Route path="/" element={<Navigate to="/Home" />} />
        <Route path="Docs" element={<Docs />} />
        <Route path="Home" element={<Home />} />
      </Route>
      <Route />
    </Routes>
  </BrowserRouter>,
  document.getElementById('root')
);
