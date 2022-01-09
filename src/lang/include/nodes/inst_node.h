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

    std::string id;

    virtual void execute();
    virtual InstNode *get_next();
};
