#include "../include/expression.h"

Expression::Expression()
{
}

Expression::Expression(Value val)
{
    value = val;
}

Expression::Expression(std::vector<ExprNode*> tl)
{
    term_list = tl;
}

void Expression::evaluate()
{
    
}

void Expression::print_expr()
{
    for (auto expr_node : term_list)
    {
        expr_node->expr_print();
    }
    std::cout << std::endl;
}