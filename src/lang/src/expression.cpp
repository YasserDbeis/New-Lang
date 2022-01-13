#include "../include/expression.h"

Expression::Expression()
{
}

Expression::Expression(Value val)
{
    value = val;
}

Expression::Expression(std::vector<ExprNode *> tl)
{
    term_list = tl;
}

void Expression::evaluate()
{
    if (term_list.empty())
    {
        return;
    }

    std::deque<ExprNode *> output_queue = infix_to_rev_polish();

    if (output_queue.empty()) // debugging purposes
    {
        std::cout << "Output queue should not be empty (BUG in expression.cpp)" << std::endl;
    }

    while (output_queue.size() >= 3)
    {
        // Extract the expression nodes
        ExprNode *exprNode1 = output_queue.front();
        output_queue.pop_front();

        ExprNode *exprNode2 = output_queue.front();
        output_queue.pop_front();

        // Extract the operator node
        ExprNode *opNode = output_queue.front();
        output_queue.pop_front();

        Value val1 = get_expr_node_value(exprNode1);
        Value val2 = get_expr_node_value(exprNode2);
        OperatorType operator_type = ((OperatorNode *)opNode)->operator_type;

        Value curr_result = compute(val1, val2, operator_type);

        // Wrap value into a constant loadnode
        LoadNode *load_const = new LoadNode(ExprType::LOAD, curr_result, -1, true);

        output_queue.push_front(load_const);
    }

    assert(output_queue.size() == 1);

    LoadNode *final_result = (LoadNode *)output_queue.back();

    value = final_result->value;
}

Value Expression::compute(Value val1, Value val2, OperatorType operator_type)
{
    assert_valid_type(val1, val2, operator_type);

    Value result;

    /*
    PLUS,
    MINUS,
    MULT,
    DIV,
    GT,
    LT,
    GEQ,
    LEQ,
    IS,
    AND,
    OR,
    XOR,
    NEQ,
    */

    if (operator_type == OperatorType::PLUS || operator_type == OperatorType::MINUS)
    {
        if ((val1.type == Type::String || val2.type == Type::String) && operator_type == OperatorType::PLUS)
        {
            std::string res_str = val1.token.lexeme + val2.token.lexeme;
            result.type = Type::String;
            result.token.type = TokenType::STRING;
            result.token.lexeme = res_str;
        }
        else if (val1.type == Type::Int && val2.type == Type::Int)
        {
            std::string int_1_str = val1.token.lexeme;
            std::string int_2_str = val2.token.lexeme;

            int int_1 = std::atoi(int_1_str.c_str());
            int int_2 = std::atoi(int_2_str.c_str());

            int sum = int_1;

            if (operator_type == OperatorType::PLUS)
            {
                sum += int_2;
            }
            else
            {
                sum -= int_2;
            }

            result.type = Type::Int;
            result.token.type = TokenType::INT_NUM;
            result.token.lexeme = std::to_string(sum);
        }
        else if (val1.type == Type::Int && val2.type == Type::Dec)
        {
            std::string int_1_str = val1.token.lexeme;
            std::string dec_1_str = val2.token.lexeme;

            int int_1 = std::atoi(int_1_str.c_str());
            double dec_1 = std::stod(dec_1_str.c_str());

            double sum = int_1;

            if (operator_type == OperatorType::PLUS)
            {
                sum += dec_1;
            }
            else
            {
                sum -= dec_1;
            }

            result.type = Type::Dec;
            result.token.type = TokenType::DEC;
            result.token.lexeme = std::to_string(sum);
        }
        else if (val1.type == Type::Dec && val2.type == Type::Int)
        {
            std::string dec_1_str = val1.token.lexeme;
            std::string int_1_str = val2.token.lexeme;

            double dec_1 = std::stod(dec_1_str.c_str());
            int int_1 = std::atoi(int_1_str.c_str());

            double sum = dec_1;

            if (operator_type == OperatorType::PLUS)
            {
                sum += int_1;
            }
            else
            {
                sum -= int_1;
            }

            result.type = Type::Dec;
            result.token.type = TokenType::DEC;
            result.token.lexeme = std::to_string(sum);
        }
        else if (val1.type == Type::Dec && val2.type == Type::Dec)
        {
            std::string dec_1_str = val1.token.lexeme;
            std::string dec_2_str = val2.token.lexeme;

            double dec_1 = std::stod(dec_1_str.c_str());
            double dec_2 = std::stod(dec_2_str.c_str());

            double sum = dec_1;

            if (operator_type == OperatorType::PLUS)
            {
                sum += dec_2;
            }
            else
            {
                sum -= dec_2;
            }

            result.type = Type::Dec;
            result.token.type = TokenType::DEC;
            result.token.lexeme = std::to_string(sum);
        }
    }

    else if (operator_type == OperatorType::NEQ)
    {
        result.type = Type::Bool;
        bool is_equal;

        if (val1.type == Type::String && val2.type == Type::String)
        {
            is_equal = val1.token.lexeme.compare(val2.token.lexeme) == 0;
        }
        else if (val1.type == Type::Bool && val2.type == Type::Bool)
        {
            is_equal = val1.token.type == val2.token.type;
        }
        else if (val1.type == Type::Int && val2.type == Type::Int)
        {
            int op1 = std::atoi(val1.token.lexeme.c_str());
            int op2 = std::atoi(val2.token.lexeme.c_str());

            is_equal = op1 == op2;
        }
        else if (val1.type == Type::Dec && val2.type == Type::Dec)
        {
            double op1 = std::stod(val1.token.lexeme.c_str());
            double op2 = std::stod(val2.token.lexeme.c_str());

            is_equal = op1 == op2;
        }

        if (is_equal == true)
        {
            result.token.type = TokenType::FALSE;
            result.token.lexeme = "false";
        }
        else
        {
            result.token.type = TokenType::TRUE;
            result.token.lexeme = "true";
        }
    }
    else // debugging
    {
        std::cout << "Invalid operator type in compute in expression.cpp" << std::endl;
        exit(EXIT_FAILURE);
    }

    return result;
}

void Expression::assert_valid_type(Value val1, Value val2, OperatorType operator_type)
{
    bool is_valid = true;

    if (val1.type == Type::Void || val2.type == Type::Void || val1.type == Type::Invalid || val2.type == Type::Invalid)
    {
        std::cout << "assert_valid_type error. One of the operands has a void or invalid type during evaluation of the expression" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (operator_type == OperatorType::PLUS)
    {
        if (val1.type == Type::Bool || val2.type == Type::Bool)
        {
            is_valid = false;
        }
    }
    else if (operator_type == OperatorType::MINUS ||
             operator_type == OperatorType::MULT ||
             operator_type == OperatorType::DIV ||
             operator_type == OperatorType::GT ||
             operator_type == OperatorType::LT ||
             operator_type == OperatorType::LEQ ||
             operator_type == OperatorType::GEQ)
    {
        if (val1.type == Type::Bool || val2.type == Type::Bool ||
            val1.type == Type::String || val2.type == Type::String)
        {
            is_valid = false;
        }
    }
    else if (operator_type == OperatorType::XOR)
    {
        if (val1.type != Type::Int || val2.type != Type::Int)
        {
            is_valid = false;
        }
    }
    else if (operator_type == OperatorType::AND ||
             operator_type == OperatorType::OR)
    {
        if (val1.type != Type::Bool || val2.type != Type::Bool)
        {
            is_valid = false;
        }
    }
    else if (operator_type == OperatorType::IS ||
             operator_type == OperatorType::NEQ)
    {
        if (val1.type != val2.type)
        {
            is_valid = false;
        }
    }

    if (is_valid == false)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Operator invalid for operands", -1, INVALID_OPERATION);
    }
}

std::deque<ExprNode *> Expression::infix_to_rev_polish()
{
    std::deque<ExprNode *> output_queue;
    std::stack<ExprNode *> op_stk;

    for (auto term : term_list)
    {
        if (term->type == ExprType::LOAD || term->type == ExprType::FUNC_CALL)
        {
            output_queue.push_back(term);
        }
        else if (term->type == ExprType::PAREN)
        {
            ParenNode *parenNode = (ParenNode *)term;
            if (parenNode->is_left == true)
            {
                op_stk.push(term);
            }
        }
        else if (term->type == ExprType::OPERATOR)
        {
            ExprNode *op1 = term;
            while (op_stk.empty() == false &&
                   op_stk.top()->type == ExprType::PAREN &&
                   compare_precedence(op1, op_stk.top()))
            {
                ExprNode *pop = op_stk.top();
                op_stk.pop();
                output_queue.push_back(pop);
            }

            op_stk.push(op1);
        }
        else if (term->type == ExprType::PAREN && is_left_paren(term) == false)
        {
            while (!op_stk.empty() && is_left_paren(op_stk.top()) == false)
            {
                ExprNode *pop = op_stk.top();
                op_stk.pop();
                output_queue.push_back(pop);
            }

            assert(!op_stk.empty() && is_left_paren(term) == true);

            ExprNode *lparen = op_stk.top();
            op_stk.pop();

            // if (!op_stk.empty() && op_stk.top().type == FUNC)
            // {
            //     Token pop = op_stk.top();
            //     op_stk.pop();
            //     output_queue.push(pop);
            // }
        }
    }

    while (op_stk.empty() == false)
    {
        assert(is_left_paren(op_stk.top()) == false);
        output_queue.push_back(op_stk.top());
        op_stk.pop();
    }

    return output_queue;
}

Value Expression::get_expr_node_value(ExprNode *exprNode)
{
    Value val;

    if (exprNode->type == ExprType::FUNC_CALL)
    {
        FuncCallNode *func_call = (FuncCallNode *)exprNode;
        // First, validate that this function call can be evaluated to a value
        if (FuncDefTable::get_return_type(func_call->get_func_id()) != Type::Void)
        {
            func_call->evaluate();
            val = func_call->value;
        }
        else
        {
            ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Evaluation encountered invalid expression operand", -1, INVALID_OPERAND);
        }
    }
    else if (exprNode->type == ExprType::LOAD)
    {
        LoadNode *load = (LoadNode *)exprNode;
        load->evaluate();
        val = load->value;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Evaluation encountered invalid expression operand", -1, INVALID_OPERAND);
    }

    return val;
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

bool Expression::compare_precedence(ExprNode *currNode1, ExprNode *topNode2)
{
    OperatorNode *op1 = (OperatorNode *)currNode1;
    OperatorNode *op2 = (OperatorNode *)topNode2;

    return ((op_to_prec[op2->operator_type]) > (op_to_prec[op1->operator_type])) ||
           ((op_to_prec[op2->operator_type] == op_to_prec[op1->operator_type]) &&
            (op_to_assoc[op2->operator_type] == Assoc::LEFT));
}

bool Expression::is_left_paren(ExprNode *exprNode)
{
    ParenNode *paren = (ParenNode *)exprNode;

    return paren->is_left == true;
}