#pragma once

#include "inst_node.h"
#include "expr_node.h"
//#include "../expression.h"
#include <string>
#include <vector>

class Expression;

class FuncCallNode : public InstNode, public ExprNode
{
public:
    Value value;

    FuncCallNode();
    FuncCallNode(std::string func_id, std::vector<Expression> args);
    FuncCallNode(ExprType expr_type, std::string func_id, std::vector<Expression> args);

    void evaluate();
    void execute() override;

    void inst_print(int num_tabs = 0) override;
    void expr_print(int num_tabs = 0) override;

    std::string get_func_id();

private:
    std::string func_id;
    std::vector<Expression> args;
};