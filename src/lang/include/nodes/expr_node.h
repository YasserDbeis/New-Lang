#pragma once

#include "../value.h"

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

private:
};