#pragma once

#include "expr_node.h"
#include <string>
#include <vector>
#include <iostream>

class LoadNode : public ExprNode
{
public:
    void evaluate();
    LoadNode();
    LoadNode(ExprType type, Type var_type, std::string name, int global_count, bool is_constant);
    LoadNode(ExprType type, Value value, int global_count, bool is_constant);

    void expr_print(int num_tabs = 0) override;

    Value value;

private:
    std::string name;
    Type var_type;
    int global_count;
    bool is_constant;
};

class ParenNode : public ExprNode
{
public:
    bool is_left;

    ParenNode();
    ParenNode(ExprType expr_type, bool is_left);

    void expr_print(int num_tabs = 0) override;
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
    XOR,
    NEQ,
};

class OperatorNode : public ExprNode
{
public:
    OperatorType operator_type;

    OperatorNode();
    OperatorNode(ExprType expr_type, OperatorType operator_type);

    void expr_print(int num_tabs = 0) override;
};