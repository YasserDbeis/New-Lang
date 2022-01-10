#pragma once

#include "token.h"
#include "error_handler.h"

enum class Type
{
    Int,
    Dec,
    String,
    Bool,
    Void,
    Invalid
};

class Value
{
public:
    Type type;
    Token token;
    Value();
    Value(Type type, Token value);

    void validate(Type expected_type); // throws error

private:
};
