/*
    Header comments
    inst_node.h -> header file for the inst_node class
*/

#pragma once

#include <string>

class InstNode
{
public:
    InstNode *next = nullptr;

#if TESTING
    std::string id;
#endif

    virtual void execute();
    virtual InstNode *get_next();
};
