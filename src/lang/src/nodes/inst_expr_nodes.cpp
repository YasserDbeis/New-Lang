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

void FuncCallNode::inst_print()
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

void FuncCallNode::expr_print()
{
    inst_print();
}