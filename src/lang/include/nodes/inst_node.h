/*
    Header comments
    inst_node.h -> header file for the inst_node class
*/

#pragma once

class InstNode
{
public:
    InstNode *next = nullptr;

    void execute();
    InstNode *get_next();
};
