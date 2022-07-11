export const docs = `
# SunLang

## TODO

# Include UML Diagram

# Include Grammar in Latex

## Arithmetic Operators

| NAME           | SYMBOL | DESCRIPTION                      | EXAMPLE |
| -------------- | ------ | -------------------------------- | ------- |
| Addition       | +      | Adds two values                  | 2 + 3   |
| Subtraction    | -      | Subtracts one value from another | 20 - 14 |
| Multiplication | \*     | Multiplies two values            | 8 \* 4  |
| Division       | /      | Divides one value from another   | 8 / 4   |

## Comparison Operators

| NAME                     | SYMBOL | DESCRIPTION                                                    | EXAMPLE |
| ------------------------ | ------ | -------------------------------------------------------------- | ------- |
| Greater than             | >      | True if left operand is greater than right operand             | 10 > 5  |
| Less than                | <      | True if left operand is less than right operand                | 20 < 80 |
| Greater than or equal to | >=     | True if left operand is greater than or equal to right operand | 8 >= 4  |
| Less than or equal to    | <=     | True if left operand is less than or equal to right operand    | 3 <= 5  |
| Equal                    | is     | True if left operand is equal to right operand                 | 5 is 5  |
| Not equal                | !=     | True if left operand is not equal to right operand             | 5 != 5  |

## Logical Operators

| NAME                 | SYMBOL | DESCRIPTION                                                                                          | EXAMPLE                  |
| -------------------- | ------ | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| Logical and          | <      | True if left operand is less than right operand                                                      | 5 < 10 and "hi" is "bye" |
| Logical or           | >=     | True if left operand is greater than or equal to right operand                                       | 5 < 10 or "hi" is "bye"  |
| Logical not          | not    | Reverses right hand operand boolean value or binary boolean operation result ??Have we implemented?? | 5 is not 5               |
| Logical not (unary)  | !      | Reverses right hand operand boolean value ??Have we implemented??                                    | !foo                     |
| Logical exclusive or | xor    | Performs exlcusive or of left and right operands                                                     | foo xor bar              |

TokenType::OPERATOR_PLUS,
TokenType::OPERATOR_MINUS,
TokenType::OPERATOR_MULT,
TokenType::OPERATOR_DIV,
TokenType::OPERATOR_GT,
TokenType::OPERATOR_LT,
TokenType::OPERATOR_GEQ,
TokenType::OPERATOR_LEQ,
TokenType::OPERATOR_IS,
TokenType::OPERATOR_AND,
TokenType::OPERATOR_OR,
TokenType::OPERATOR_NOT,
TokenType::OPERATOR_XOR,
TokenType::OPERATOR_XCL,
TokenType::OPERATOR_NEQ,
->

## END OF OUR DOCS
`;
