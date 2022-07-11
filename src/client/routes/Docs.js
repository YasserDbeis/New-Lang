import React from 'react';
import { useState } from 'react';
import { ReactMarkdown } from 'react-markdown/lib/react-markdown';
import { docs } from '../content/Docs';
import remarkGfm from 'remark-gfm';
import '../styles/Docs.css';

const Docs = (props) => {
  return <ReactMarkdown children={docs} remarkPlugins={remarkGfm} />;
};

export default Docs;
