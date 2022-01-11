#include "../../include/nodes/inst_expr_nodes.h"

/* ----------------------------------------------
FuncCallNode Implementation
---------------------------------------------- */

FuncCallNode::FuncCallNode()
{
}

FuncCallNode::FuncCallNode(std::string func_id, std::vector<Expression> args)
{
    this->func_id = func_id;
    this->args = args;
}

FuncCallNode::FuncCallNode(ExprType type, std::string func_id, std::vector<Expression> args)
{
    this->func_id = func_id;
    this->type = type;
    this->func_id = func_id;
    this->args = args;
}

/* Override */
void FuncCallNode::execute()
{
    /*
        create new stack frame

        for (arg in args)
        {
            arg_stack.push(arg.evaluate())
        }

        execute_instructions(func_table[id].head);

        value = stack_trace.peek().scope_tree.return_value

        remove stack frame
    */
}

void FuncCallNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::cout << "[Func Call] Offset: " << this->get_offset() << ", Func Name: " << func_id << std::endl;
    if (args.empty())
    {
        for (int i = 0; i < num_tabs; i++)
        {
            std::cout << "\t";
        }

        std::cout << "\tFunc Arguments: none" << std::endl;
    }
    else
    {
        int i = 0;
        for (auto arg : args)
        {
            arg.print_expr(num_tabs + 1);
            i++;
        }
    }
}

void FuncCallNode::expr_print(int num_tabs)
{
    inst_print(num_tabs);
}