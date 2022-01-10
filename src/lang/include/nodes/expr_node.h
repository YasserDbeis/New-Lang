#pragma once

#include "../value.h"
#include <iostream>

enum class ExprType
{
    FUNC_CALL,
    LOAD,
    PAREN,
    OPERATOR
};

class ExprNode
{
public:
    ExprType type;

    virtual void expr_print() 
    {
        std::cout << "Default expr print" << std::endl;
    }

private:
};