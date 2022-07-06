import React from 'react';
import { useState } from 'react';
import AceEditor from 'react-ace';
import 'ace-builds/src-noconflict/theme-solarized_light';
import 'ace-builds/src-noconflict/ext-language_tools';
import 'ace-builds/src-noconflict/mode-golang';
import 'ace-builds/src-noconflict/theme-monokai';
import axios from 'axios';
import qs from 'qs';

const Home = (props) => {
  const [code, setCode] = useState(null);
  const [output, setOutput] = useState(null);

  const onCodeChange = (newCode) => {
    setCode(newCode);
  };

  const runCode = () => {
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
    <div>
      <button onClick={runCode}>Run Code</button>
      <div style={{ fontSize: '12px', whiteSpace: 'pre' }}>{output}</div>
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
        }}
      />
    </div>
  );
};

export default Home;
