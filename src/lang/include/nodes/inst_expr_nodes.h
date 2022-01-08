#pragma once

#include "inst_node.h"
#include "expr_node.h"
#include "../expression.h"
#include <string>
#include <vector>

class FuncCallNode : public InstNode, public ExprNode
{
public:
    Value return_value;

    void execute() override;
    Value evaluate();

private:
    std::string id;
    std::vector<Expression> args;
};