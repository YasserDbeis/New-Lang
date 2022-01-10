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