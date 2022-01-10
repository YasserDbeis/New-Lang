#include "../../include/nodes/inst_node.h"

void InstNode::set_offset(int new_offset)
{
    offset = new_offset;
}

int InstNode::get_offset()
{
    return offset;
}

void InstNode::execute()
{
    /* Does nothing unless overridden by child class */
}

void InstNode::inst_print()
{
    std::cout << "Default called\n";
}