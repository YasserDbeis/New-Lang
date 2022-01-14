/*
    Header comments
    inst_node.h -> header file for the inst_node class
*/

#pragma once

#include <string>
#include <iostream>

enum class InstType
{
    STORE,
    RETURN,
    JMP,
    CJMP,
    FUNC_CALL,
    SCOPE
};

class InstNode
{
public:
    virtual void execute();
    virtual int get_offset();

    void set_offset(int new_offset);
    int get_target();

    virtual void inst_print(int num_tabs = 0);

    InstType inst_type;

private:
    int offset = 1;
};
