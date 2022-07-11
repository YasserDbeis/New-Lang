import AceEditor from 'react-ace';
import axios from 'axios';
import { IoMdPlay } from 'react-icons/io';
import { getProgText } from '../content/SamplePrograms';
import React from 'react';
import qs from 'qs';
import { useState } from 'react';
import { FormControl, InputLabel, Select, MenuItem } from '@mui/material';
import 'ace-builds/src-noconflict/theme-solarized_light';
import 'ace-builds/src-noconflict/ext-language_tools';
import 'ace-builds/src-noconflict/mode-golang';
import 'ace-builds/src-noconflict/theme-monokai';
import '../styles/Home.css';

const Home = (props) => {
  const [output, setOutput] = useState(null);
  const samplePrograms = [
    'Hello, World!',
    'Fibonacci (Iterative)',
    'Fibonacci (Recursive)',
  ];

  const DEFAULT_PROG = samplePrograms[0];
  const [sampleProgram, setSampleProgram] = useState(DEFAULT_PROG);
  const [code, setCode] = useState(getProgText(DEFAULT_PROG));

  const onCodeChange = (newCode) => {
    setCode(newCode);
  };

  const onSampleProgSelect = (event) => {
    setSampleProgram(event.target.value);
    console.log('TEXT', event.target.value);
    setCode(getProgText(event.target.value));
  };

  const runCode = () => {
    if (code == null) {
      return;
    }

    var data = qs.stringify({
      code,
    });
    var config = {
      method: 'post',
      url: 'http://localhost:8080/api/runCode',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      data: data,
    };

    axios(config)
      .then((res) => {
        console.log(res);
        setOutput(res.data);
      })
      .catch((err) => {
        console.log(err);
      });
  };
  return (
    <div id="home-container">
      <div id="code-control-bar">
        <FormControl>
          <InputLabel id="template-select-input-label">
            Sample Program
          </InputLabel>
          <Select
            labelId="template-select-label"
            id="template-select"
            value={sampleProgram}
            label="Sample Program"
            onChange={onSampleProgSelect}
          >
            {samplePrograms.map((sampleProgram) => {
              return <MenuItem value={sampleProgram}>{sampleProgram}</MenuItem>;
            })}
          </Select>
        </FormControl>
        <IoMdPlay
          id="code-control-bar-play-button"
          style={{ height: '80%', width: 'auto', color: 'green' }}
          onClick={runCode}
          title="Run Code"
        />
      </div>
      <div id="code-editor">
        <AceEditor
          placeholder="Placeholder Text"
          mode="golang"
          theme="monokai"
          name="blah2"
          // onLoad={this.onLoad}
          onChange={onCodeChange}
          fontSize={14}
          showPrintMargin={false}
          showGutter={true}
          highlightActiveLine={true}
          value={code}
          setOptions={{
            enableBasicAutocompletion: true,
            enableLiveAutocompletion: true,
            enableSnippets: false,
            showLineNumbers: true,
            tabSize: 4,
          }}
          style={{
            width: '100%',
            height: '100%',
          }}
        />
      </div>
      <div id="code-output">{output}</div>
    </div>
  );
};

export default Home;
