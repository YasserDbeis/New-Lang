#pragma once

#include "value.h"
#include "nodes/expr_nodes.h"
#include <vector>

class Expression
{
    Value value;
    std::vector<ExprNode> term_list;

    Expression(std::vector<ExprNode> terms);
    Expression(Value value);
    void evaluate();
};