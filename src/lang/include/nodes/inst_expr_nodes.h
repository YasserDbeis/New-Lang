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

    void inst_print() override
    {
        std::cout << "Func Call // OFFSET: " << this->get_offset() << " FUNC ID: " << func_id << " ";
        if (args.empty())
        {
            std::cout << "ARGUMENTS: none" << std::endl;
        }
        else
        {
            // print arguments
        }
    }

private:
    std::string func_id;
    std::vector<Expression> args;
};