const path = require('path');
const { promisify } = require('util');
const exec = promisify(require('child_process').exec);

// Runs the SunLang interpreter with the source code associated with the given uuid
// Input: uuid (file name of input source code living in ./code/)
// Output: Program output (text) if successful, null otherwise
const runCode = async (uuid) => {
  try {
    const sunLangBinaryPath = path.join(__dirname, '..', 'lang', 'a.out');
    const inputFilePath = path.join(__dirname, 'code', uuid.toString());
    const codeOutput = await exec(`${sunLangBinaryPath} 2 < ${inputFilePath}`);

    return codeOutput.stdout.trim();
  } catch (error) {
    console.log(error);
    return null;
  }
};

// Export the function for usage in index.js
module.exports = {
  runCode,
};
