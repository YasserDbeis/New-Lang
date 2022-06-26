const bodyParser = require('body-parser');
var cors = require('cors');
const express = require('express');
const fs = require('fs')
const os = require('os');
const path = require('path');
const { v4: getUUID } = require('uuid') 

const { runCode } = require('./run_code.js');

const app = express();

app.use(express.static('dist'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cors());
app.get('/api/getUsername', (req, res) =>
  res.send({ username: os.userInfo().username })
);

// API responsible for running user source code and returning the SunLang
//   interpreter output
// Input: Source code (text) through req.body
// Output: Program output (text) with status 200 if successful, status 500 otherwise
app.post('/api/runCode', async (req, res) => {
  // Get the user-input source code
  const { code } = req.body;

  if (!code) {
    return res.sendStatus(500);
  }

  // Generate a unique UUID for file creation on the server-side
  const uuid = getUUID();

  // Create the code directory to store input source code if it doesn't exist
  if (!fs.existsSync(path.join(__dirname, 'code'))) {
    fs.mkdirSync(path.join(__dirname, 'code'));
  }

  // Create a file containing the user source code to run
  fs.writeFileSync(path.join(__dirname, `code/${uuid}`), code.toString());

  // Run the interpreter with the inputFile
  const output = await runCode(uuid);

  // Delete the user input file if it exists
  fs.unlinkSync(path.join(__dirname, `code/${uuid}`));

  if (output == null) {
    return res.sendStatus(500);
  }

  // Send the output of the program execution back to the client
  res.status(200).send(output);
});

app.listen(process.env.PORT || 8080, () => {
  console.log(`Listening on port ${process.env.PORT || 8080}!`);
});
