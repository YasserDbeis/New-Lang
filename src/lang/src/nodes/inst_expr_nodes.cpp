#include "../../include/nodes/inst_expr_nodes.h"

/* ----------------------------------------------
FuncCallNode Implementation
---------------------------------------------- */

FuncCallNode::FuncCallNode()
{
}

FuncCallNode::FuncCallNode(std::string id, std::vector<Expression> args)
{
    this->id = id;
    this->args = args;
}

FuncCallNode::FuncCallNode(ExprType type, std::string id, std::vector<Expression>)
{
    this->type = type;
    FuncCallNode(id, args);
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