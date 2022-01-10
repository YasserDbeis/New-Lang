#include "../../include/nodes/inst_nodes.h"

/* --------------------------------------------
JmpNode implementation
--------------------------------------------- */

JmpNode::JmpNode()
{
    this->id = "JUMP NODE";
}

// Why not just return next? No need for override

/* --------------------------------------------
CjmpNode implementation
--------------------------------------------- */

CjmpNode::CjmpNode()
{
    this->id = "CJMP NODE";
}

CjmpNode::CjmpNode(Expression expr)
{
    this->expr = expr;
    this->id = "CJMP NODE";
}

void CjmpNode::execute()
{
    //expr.evaluate();
}

/* --------------------------------------------
StoreNode implementation
--------------------------------------------- */

StoreNode::StoreNode()
{
    this->id = "STORE NODE";
}

StoreNode::StoreNode(Type type, std::string name, Expression expr, int global_count, bool is_param)
{
    this->type = type;
    this->name = name;
    this->expr = expr;
    this->global_count = global_count;
    this->is_param = is_param;

    this->id = "STORE NODE";
}

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

ReturnNode::ReturnNode()
{
    this->id = "RETURN NODE";
}

void ReturnNode::set_no_expr()
{
    expr_exists = false;
}

void ReturnNode::set_expr(Expression given_expr)
{
    expr = given_expr;
}

void ReturnNode::execute()
{
    //expr.evaluate();
    /*
        stack_trace.peek().scope_tree.return_value = expr.value;

        // Note, we can put a node value at return_value if we reach nullptr when executing function (not global ll)
    */
}

/* --------------------------------------------
ScopeNode implementation
--------------------------------------------- */

ScopeNode::ScopeNode()
{
    this->id = "SCOPE NODE";
}

ScopeNode::ScopeNode(bool is_new_scope)
{
    this->is_new_scope = is_new_scope;
    this->id = "SCOPE NODE";
}

void ScopeNode::execute()
{
}