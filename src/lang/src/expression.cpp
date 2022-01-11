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

void Expression::print_expr(int num_tabs)
{
    if (term_list.empty())
    {
        for (int i = 0; i < num_tabs; i++)
        {
            std::cout << "\t";
        }
        std::cout << "No expression!" << std::endl;
    }
    else
    {
        for (auto expr_node : term_list)
        {
            expr_node->expr_print(num_tabs);
        }
    }
}