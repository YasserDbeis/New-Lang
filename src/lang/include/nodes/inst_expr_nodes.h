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
        std::cout << "Func Call // OFFSET: " << this->get_offset() << " FUNC ID: " << func_id << std::endl;
        if (args.empty())
        {
            std::cout << "ARGUMENTS: none" << std::endl;
        }
        else
        {
            int i = 0;
            for (auto arg : args)
            {
                std::cout << "arg " << i << ": ";
                arg.print_expr();
                i++;
            }
        }
    }


    void expr_print() override
    {
        inst_print();
    }

private:
    std::string func_id;
    std::vector<Expression> args;
};