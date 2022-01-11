#pragma once

#include "value.h"
#include "nodes/expr_nodes.h"
#include <vector>

class Expression
{
public:
    Value value;
    std::vector<ExprNode*> term_list;

    Expression();
    Expression(std::vector<ExprNode*> terms);
    Expression(Value value);
    void evaluate();

    void print_expr(int num_tabs = 0);
};