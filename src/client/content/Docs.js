export const docs = `
# SunLang

## TODO

# Include UML Diagram

# Include Grammar in Latex

## Arithmetic Operators

| NAME           | SYMBOL | DESCRIPTION                                | EXAMPLE |
| :------------: | :----: | :----------------------------------------: | :-----: |
| Addition       | +      | Adds two numerical values                  | 2 + 3   |
| Subtraction    | -      | Subtracts one numerical value from another | 20 - 14 |
| Multiplication | \*     | Multiplies two numerivalues                | 8 \* 4  |
| Division       | /      | Divides one numerical value from another   | 8 / 4   |

## Comparison Operators

| NAME                     | SYMBOL | DESCRIPTION                                                              | EXAMPLE |
| ------------------------ | ------ | ------------------------------------------------------------------------ | ------- |
| Greater than             | >      | True if left numerical operand is greater than right operand             | 10 > 5  |
| Less than                | <      | True if left numerical operand is less than right operand                | 20 < 80 |
| Greater than or equal to | >=     | True if left numerical operand is greater than or equal to right operand | 8 >= 4  |
| Less than or equal to    | <=     | True if left numerical operand is less than or equal to right operand    | 3 <= 5  |
| Equal                    | is     | True if left operand is equal to right operand                           | 5 is 5  |
| Not equal                | !=     | True if left operand is not equal to right operand                       | 5 != 5  |

## Logical Operators

| NAME                 | SYMBOL   | DESCRIPTION                                            | EXAMPLE                  |
| -------------------- | -------- | ------------------------------------------------------ | ------------------------ |
| Logical not (unary)  | ! &#124; not | Negates right hand boolean value                       | !true &#124; not false          |
| Logical and          | and      | Performs logical and operation on two boolean operands | 5 < 10 and "hi" is "bye" |
| Logical or           | or       | Performs logical or operation on two boolean operands  | 5 < 10 or "hi" is "bye"  |
| Logical exclusive or | xor      | Performs exclusive-or on two boolean operands          | false xor true              |

<!-- TokenType::OPERATOR_PLUS,
TokenType::OPERATOR_MINUS,
TokenType::OPERATOR_MULT,
TokenType::OPERATOR_DIV, -->
<!-- TokenType::OPERATOR_GT, -->
<!-- TokenType::OPERATOR_LT, -->
<!-- TokenType::OPERATOR_GEQ,
TokenType::OPERATOR_LEQ, -->
<!-- TokenType::OPERATOR_IS, -->

TokenType::OPERATOR_AND,
TokenType::OPERATOR_OR,
TokenType::OPERATOR_NOT,
TokenType::OPERATOR_XOR,
TokenType::OPERATOR_XCL,

<!-- TokenType::OPERATOR_NEQ, -->

->

## END OF OUR DOCS
`;
