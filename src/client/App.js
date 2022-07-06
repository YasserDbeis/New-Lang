import React, { Component } from 'react';
import './app.css';
import ReactImage from './react.png';

import { Link, Outlet } from 'react-router-dom';

import NavBar from './NavBar';

export default class App extends Component {
  render() {
    return (
      <div>
        <NavBar />
        <Outlet />
      </div>
    );
  }
}
