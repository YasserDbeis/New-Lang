const path = require('path');
const { promisify } = require('util');
const exec = promisify(require('child_process').exec);

const runCode = async (uuid) => {
  try {
    const binaryPath = path.join(__dirname, '../lang/a.out');
    const inputFilePath = path.join(__dirname, 'code', uuid.toString());
    const codeOutput = await exec(`${binaryPath} 2 < ${inputFilePath}`);

    return codeOutput.stdout.trim();
  } catch (error) {
    console.log(error);
    return null;
  }
};

module.exports = {
  runCode,
};
