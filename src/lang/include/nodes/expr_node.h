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
    ExprType expr_type;

    virtual void expr_print(int num_tabs = 0) {}
};