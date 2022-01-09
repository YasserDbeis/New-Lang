#include "../../include/nodes/expr_nodes.h"

/* --------------------------------------------
LoadNode implementation
--------------------------------------------- */

LoadNode::LoadNode()
{
}

LoadNode::LoadNode(ExprType type, std::string name, int global_count, bool is_constant)
{
    this->type = type;
    this->name = name;
    this->global_count = global_count;
    this->is_constant = is_constant;
}

Value LoadNode::evaluate()
{
    if (is_constant)
    {
        return value;
    }

    /* Search through scope tree for variable
        If not found, consult global hashtable of vars with global_count
        If still not found, throw an error
    */
}

/* --------------------------------------------
ParenNode implementation
--------------------------------------------- */

ParenNode::ParenNode()
{
}

ParenNode::ParenNode(ExprType type, bool is_left)
{
    this->type = type;
    this->is_left = is_left;
}

// Nothing to do

/* --------------------------------------------
OperatorNode implementation
--------------------------------------------- */

OperatorNode::OperatorNode()
{
}

OperatorNode::OperatorNode(ExprType type, OperatorType)
{
}

// Nothing to do
