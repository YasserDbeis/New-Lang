#include "../../include/nodes/inst_nodes.h"

/* --------------------------------------------
JmpNode implementation
--------------------------------------------- */

// Why not just return next? No need for override

/* --------------------------------------------
CjmpNode implementation
--------------------------------------------- */
void CjmpNode::execute()
{
    expr.evaluate();
}

InstNode *CjmpNode::get_next()
{
    if (expr.value.value.type == TokenType::TRUE)
    {
        return next;
    }
    else if (expr.value.value.type == TokenType::FALSE)
    {
        return target;
    }
    else
    {
        // Error
    }
}

/* --------------------------------------------
StoreNode implementation
--------------------------------------------- */
void StoreNode::execute()
{
    /*

    if (is_param)
    {
        value = arg_stack.pop();
    } else
    {
        expr.evaluate();

        if (is global)
        {
            if (global_table[name] already exists)
                error
            else
                global_table[name] = {new Value {expr.value, type}, global_count}
        } else // put it in scope tree
        {
            stack_trace.peek().scope_tree.push(new Value {expr.value, type});
        }
    }




    */
}

/* --------------------------------------------
ReturnNode implementation
--------------------------------------------- */
void ReturnNode::execute()
{
    expr.evaluate();
    /*
        stack_trace.peek().scope_tree.return_value = expr.value;

        // Note, we can put a node value at return_value if we reach nullptr when executing function (not global ll)
    */
}