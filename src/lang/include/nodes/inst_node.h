/*
    Header comments
    inst_node.h -> header file for the inst_node class
*/

#pragma once

#include <string>

class InstNode
{
public:
    std::string id;

    virtual void execute();
    int get_offset();
    void set_offset(int new_offset);

private:
    int offset = 1;
};
