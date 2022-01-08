#include "../include/value.h"

// class Value
// {
// public:
//     Type type;
//     Token value;
//     Value();
//     Value(Type _type, Token _value);

// private:
//     void validate(); // throws error
// };

Value::Value()
{
}

Value::Value(Type type, Token token)
{
    this->type = type;
    this->token = token;
}

void Value::validate(Type expected_type)
{
    if (type != expected_type)
    {
        // throw error
    }
}