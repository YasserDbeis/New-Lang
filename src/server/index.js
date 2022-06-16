const express = require('express');
const os = require('os');
const tester = require('../../build/Release/main');
const bodyParser = require('body-parser');

const app = express();

app.use(express.static('dist'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.get('/api/getUsername', (req, res) =>
  res.send({ username: os.userInfo().username })
);

app.post('/api/runCode', async (req, res) => {
  // console.log('BODY', req);
  const { code } = req.body;
  const resp = tester.testLang(code);
  console.log('API RESPONSE', resp);
  res.status(200).send(resp);
});

app.listen(process.env.PORT || 8080, () => {
  console.log(`Listening on port ${process.env.PORT || 8080}!`);
  // console.log(tester.testLang('HELLO WORLD!'));
});
