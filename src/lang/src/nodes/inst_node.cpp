#include "../../include/nodes/inst_node.h"

InstNode *InstNode::get_next()
{
    return next;
}

void InstNode::execute()
{
    /* Does nothing unless overridden by child class */
}