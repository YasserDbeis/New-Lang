import AceEditor from 'react-ace';
import axios from 'axios';
import { IoMdPlay } from 'react-icons/io';
import { getProgText } from '../content/SamplePrograms';
import React from 'react';
import qs from 'qs';
import { useState } from 'react';
import {
  FormControl,
  InputLabel,
  Select,
  MenuItem,
  Button,
} from '@mui/material';
import 'ace-builds/src-noconflict/theme-solarized_light';
import 'ace-builds/src-noconflict/ext-language_tools';
import 'ace-builds/src-noconflict/mode-golang';
import 'ace-builds/src-noconflict/theme-monokai';
import '../styles/Home.css';
import '../../client/app.css';

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
      url: `https://sunlang.org/api/runCode`,
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      data: data,
    };

    axios(config)
      .then((res) => {
        console.log(res);
        setOutput(res.data.toString());
      })
      .catch((err) => {
        console.log(err);
      });
  };
  return (
    <div id="home-container">
      <div id="code-control-bar">
        <ProgramDropdown
          onSampleProgSelect={onSampleProgSelect}
          sampleProgram={sampleProgram}
          samplePrograms={samplePrograms}
        />
        <Button
          variant="contained"
          sx={{
            borderRadius: 28,
            m: 1,
            fontFamily: 'Reem Kufi Fun',
            background: '#ff6400',
            '&:hover': {
              background: '#ff7f00',
            },
            boxShadow: 'none !important',
          }}
          onClick={runCode}
          title="Run Code"
          startIcon={<IoMdPlay />}
        >
          Run
        </Button>
      </div>
      <div id="code-editor">
        <AceEditor
          placeholder="Placeholder Text"
          mode="golang"
          theme="github"
          name="blah2"
          onChange={onCodeChange}
          fontSize={14}
          showPrintMargin={false}
          showGutter={true}
          highlightActiveLine={true}
          value={code}
          setOptions={{
            enableBasicAutocompletion: false,
            enableLiveAutocompletion: false,
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

const ProgramDropdown = (props) => {
  return (
    <FormControl sx={{ m: 1 }}>
      <Select
        value={props.sampleProgram}
        onChange={props.onSampleProgSelect}
        inputProps={{ 'aria-label': 'Without label' }}
        sx={{
          fontFamily: 'Reem Kufi Fun',
          color: 'white',
          backgroundColor: '#ff6400',
          fontSize: '14px',
          '.MuiOutlinedInput-notchedOutline': {
            border: 'none',
          },
          '&.Mui-focused .MuiOutlinedInput-notchedOutline': {
            border: 'none',
            color: 'white',
          },
          '&:hover .MuiOutlinedInput-notchedOutline': {
            border: 'none',
            color: 'white',
          },
          '.MuiSvgIcon-root ': {
            fill: 'white !important',
          },
        }}
      >
        {props.samplePrograms.map((program) => (
          <MenuItem
            key={program}
            value={program}
            sx={{
              fontFamily: 'Reem Kufi Fun',
              fontSize: '14px',
            }}
          >
            {program.toUpperCase()}
          </MenuItem>
        ))}
      </Select>
    </FormControl>
  );
};

export default Home;
