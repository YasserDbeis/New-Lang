#include "../include/expression.h"

Expression::Expression()
{
}

Expression::Expression(Value val)
{
    value = val;
}

Expression::Expression(std::vector<ExprNode> tl)
{
    term_list = tl;
}

void Expression::evaluate()
{
    
}