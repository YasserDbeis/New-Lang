#pragma once

#include "token.h"
#include "error_handler.h"

enum class Type
{
    Int,
    Dec,
    String,
    Bool,
    Void
};

class Value
{
public:
    Type type;
    Token value;

    Value(Type _type, Token _value);

private:
    void validate(); // throws error
};
