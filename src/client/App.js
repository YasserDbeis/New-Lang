import React, { Component } from 'react';
import './app.css';
import ReactImage from './react.png';
import AceEditor from 'react-ace';
import 'ace-builds/src-noconflict/theme-solarized_light';
import 'ace-builds/src-noconflict/ext-language_tools';
import 'ace-builds/src-noconflict/mode-c_cpp';
import 'ace-builds/src-noconflict/theme-monokai';
import axios from 'axios';
import qs from 'qs';

export default class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      username: null,
      code: null,
    };
  }

  componentDidMount() {
    fetch('/api/getUsername')
      .then((res) => res.json())
      .then((user) => this.setState({ username: user.username }));
  }

  onCodeChange = (newCode) => {
    this.setState({ code: newCode });
  };

  runCode = () => {
    var data = qs.stringify({
      code: this.state.code,
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
      })
      .catch((err) => {
        console.log(err);
      });
  };

  render() {
    const { username } = this.state;
    return (
      <div>
        {username ? (
          <h1>{`Hello ${username}`}</h1>
        ) : (
          <h1>Loading.. please wait!</h1>
        )}
        <img src={ReactImage} alt="react" />
        <AceEditor
          placeholder="Placeholder Text"
          mode="c_cpp"
          theme="monokai"
          name="blah2"
          // onLoad={this.onLoad}
          onChange={this.onCodeChange}
          fontSize={14}
          showPrintMargin={true}
          showGutter={true}
          highlightActiveLine={true}
          value={this.state.code}
          setOptions={{
            enableBasicAutocompletion: true,
            enableLiveAutocompletion: true,
            enableSnippets: false,
            showLineNumbers: true,
            tabSize: 2,
          }}
        />
        <button onClick={this.runCode}>Run Code</button>
      </div>
    );
  }
}
