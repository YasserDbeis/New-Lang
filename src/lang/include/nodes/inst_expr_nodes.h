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

    FuncCallNode();
    FuncCallNode(std::string func_id, std::vector<Expression> args);
    FuncCallNode(ExprType type, std::string func_id, std::vector<Expression> args);

private:
    std::string func_id;
    std::vector<Expression> args;
};