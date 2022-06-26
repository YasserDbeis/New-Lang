const express = require('express');
const os = require('os');
var cors = require('cors');
const tester = require('../../build/Release/main');
const bodyParser = require('body-parser');
const { runCode } = require('./run_code.js');
const { v4: getUUID } = require('uuid'), // uuid generator
  fs = require('fs'),
  path = require('path');

const app = express();

app.use(express.static('dist'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cors());
app.get('/api/getUsername', (req, res) =>
  res.send({ username: os.userInfo().username })
);

app.post('/api/runCode', async (req, res) => {
  // Get the user-inputted source code
  const { code } = req.body;

  if (!code) {
    res.sendStatus(500);
    return;
  }

  // Generate a unique UUID for file creation on the server-side
  const uuid = getUUID();

  // Create a file containing the user source code to run
  fs.writeFileSync(path.join(__dirname, `code/${uuid}`), code.toString());

  // Run the interpreter with the inputFile
  const output = await runCode(uuid);

  // Delete the user input file if it exists
  fs.unlinkSync(path.join(__dirname, `code/${uuid}`));

  if (output == null) {
    res.sendStatus(500);
    return;
  }

  // Send the output of the program execution back to the client
  res.status(200).send(output);
});

app.listen(process.env.PORT || 8080, () => {
  console.log(`Listening on port ${process.env.PORT || 8080}!`);
  // console.log(tester.testLang('HELLO WORLD!'));
});
