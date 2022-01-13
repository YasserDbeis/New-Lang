/*
    Header comments
    inst_node.h -> header file for the inst_node class
*/

#pragma once

#include <string>
#include <iostream>

class InstNode
{
public:
    virtual void execute();
    int get_offset();
    void set_offset(int new_offset);

    virtual void inst_print(int num_tabs = 0);

private:
    int offset = 1;
};
