#pragma once

#include "expr_node.h"
#include <string>
#include <vector>

class LoadNode : public ExprNode
{
public:
    std::string name;
    int global_count;
    Value value;
    bool is_constant;

    Value evaluate();
};

class ParenNode : public ExprNode
{
public:
    bool is_left;
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
    XCL,
    NEQ,
};

class OperatorNode : public ExprNode
{
public:
    OperatorType operator_type;
};