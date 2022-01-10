#pragma once

#include "expr_node.h"
#include <string>
#include <vector>
#include <iostream>

class LoadNode : public ExprNode
{
public:
    Value evaluate();
    LoadNode();
    LoadNode(ExprType type, Type var_type, std::string name, int global_count, bool is_constant);
    LoadNode(ExprType type, Value value, int global_count, bool is_constant);

    void expr_print() override
    {
        std::unordered_map<Type, std::string> type_to_str = {
            {Type::Bool, "Bool"},
            {Type::Dec, "Dec"},
            {Type::Int, "Int"},
            {Type::Invalid, "Invalid"},
            {Type::String, "String"},
            {Type::Void, "Void"}};

        std::unordered_map<TokenType, Type> token_to_type =
        {
                {TokenType::BOOL, Type::Bool},
                {TokenType::TRUE, Type::Bool},
                {TokenType::FALSE, Type::Bool},
                {TokenType::STR, Type::String},
                {TokenType::STRING, Type::String},
                {TokenType::DEC, Type::Dec},
                {TokenType::DEC_NUM, Type::Dec},
                {TokenType::INT, Type::Int},
                {TokenType::INT_NUM, Type::Int},
                {TokenType::VOID, Type::Void}};

        std::cout << "LOAD // "
            << "is_constant: " << is_constant
            << ", value: " << type_to_str[token_to_type[value.token.type]] << " " << value.token.lexeme
            << ", name: " << name
            << ", type: " << type_to_str[var_type]
            << ", global count: " << global_count << std::endl;
    }

private:
    std::string name;
    Type var_type;
    int global_count;
    Value value;
    bool is_constant;
};

class ParenNode : public ExprNode
{
public:
    bool is_left;

    ParenNode();
    ParenNode(ExprType type, bool is_left);

    void expr_print() override
    {
        if (is_left == true)
        {
            std::cout << "(" << std::endl;
        }
        else
        {
            std::cout << ")" << std::endl;
        }
    }
};

enum class OperatorType
{
    PLUS,
    MINUS,
    MULT,
    DIV,
    GT,
    LT,
    GEQ,
    LEQ,
    IS,
    AND,
    OR,
    NOT,
    XOR,
    XCL,
    NEQ,
};

class OperatorNode : public ExprNode
{
public:
    OperatorType operator_type;

    OperatorNode();
    OperatorNode(ExprType type, OperatorType operator_type);

    void expr_print() override
    {
        std::unordered_map<OperatorType, std::string> operator_type_to_str =
        {
            {OperatorType::PLUS, "+"},
            {OperatorType::MINUS, "-"},
            {OperatorType::MULT, "*"},
            {OperatorType::DIV, "/"},
            {OperatorType::GT, ">"},
            {OperatorType::LT, "<"},
            {OperatorType::GEQ, ">="},
            {OperatorType::LEQ, "<="},
            {OperatorType::IS, "is"},
            {OperatorType::AND, "and"},
            {OperatorType::OR, "or"},
            {OperatorType::NOT, "not"},
            {OperatorType::XOR, "xor"},
            {OperatorType::XCL, "!"},
            {OperatorType::NEQ, "!="}
          };
          
          std::cout << operator_type_to_str[operator_type] << std::endl;
    }
};