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
