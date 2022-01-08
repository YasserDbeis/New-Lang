#include "../../include/nodes/inst_expr_nodes.h"

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