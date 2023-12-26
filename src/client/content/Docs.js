export const docs = `
# SunLang Documentation

Welcome to the official documentation for SunLang. This guide will help you understand the syntax and features of SunLang.

## Types

SunLang supports the following basic data types:

| Type  | Description                         | Example                              |
| ----- | ----------------------------------- | ------------------------------------ |
| int   | Integer values                      | \`int x = 42;\`                      |
| dec   | Decimal (floating point) values     | \`dec pi = 3.14;\`                   |
| bool  | Boolean values (\`true\`/\`false\`) | \`bool isTrue = true;\`              |
| str   | String values                       | \`str message = "Hello, SunLang!";\` |
| void  | No return value in functions        | \`func example() -> void {}\`        |

*Note: the void return type is optional.*

## Operators

### Arithmetic Operators

SunLang includes standard arithmetic operators:

| Operator | Description    | Example                  |
| -------- | -------------- | ------------------------ |
| +        | Addition       | \`int sum = 5 + 3;\`     |
| -        | Subtraction    | \`int diff = 8 - 2;\`    |
| \*       | Multiplication | \`int product = 4 * 2;\` |
| /        | Division       | \`dec quotient = 8 / 2;\`|

### Comparison Operators

SunLang supports various comparison operators:

| Operator | Description                | Example                         |
| -------- | -------------------------- | ------------------------------- |
| >        | Greater than               | \`bool greater = x > y;\`       |
| <        | Less than                  | \`bool less = x < y;\`          |
| >=       | Greater than or equal to   | \`bool greaterEqual = x >= y;\` |
| <=       | Less than or equal to      | \`bool lessEqual = x <= y;\`    |
| is       | Equality                   | \`bool isEqual = x is y;\`      |
| !=       | Inequality                 | \`bool notEqual = x != y;\`     |

### Logical Operators

SunLang includes logical operators:

| Operator | Description         | Example                          |
| -------- | ------------------- | -------------------------------- |
| not      | Logical NOT         | \`bool result = not condition;\` |
| xor      | Logical XOR         | \`bool result = x xor y;\`       |
| and      | Logical AND         | \`bool result = x and y;\`       |
| or       | Logical OR          | \`bool result = x or y;\`        |

## Control Flow

### Conditional Statements

SunLang supports conditional statements:

Example:

\`\`\`
  if (condition) {
      // Code block
  } elseif (another condition) {
      // Code block
  } else {
      // Code block
  }
\`\`\`

### Loops

SunLang supports the while-loop:

Example:

\`\`\`
  while (condition) {
      // Code block 
  }
\`\`\`

## Functions

SunLang allows you to define and use functions:

\`\`\`
  func add(int x, int y) -> int {
      return x + y;
  }

  ~ -- snip --

  int result = add(5, 10);
  print("The result is " + result); ~ expected output: 15

  ~ -- snip --
\`\`\`

### Built-in print Function

SunLang includes a built-in print function, which supports data concatenation, for output:

\`\`\`
  print("Hello, " + "world!");
\`\`\`

## Entry Point

Every SunLang program must define a special function called \`main()\`. This function serves as the entry point for the program:

\`\`\`
  func main() {
      // Your main program logic goes here
  }
\`\`\`

## Comments

Comments in SunLang are denoted by the tilde (~) symbol:

\`\`\`
  ~ This is a comment in SunLang
\`\`\`


Feel free to explore SunLang further by inspecting our built in programs or create your own. Happy coding!
`;
