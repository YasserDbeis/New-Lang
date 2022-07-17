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
    value.token.line_number = 1;
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

/* BEGINNING OF COMPUTE HELPER FUNCTIONS */

auto Expression::arith_compute(Value val1, Value val2, OperatorType operator_type)
{
    std::string val_1_str = val1.token.lexeme;
    std::string val_2_str = val2.token.lexeme;

    auto val_1_num = val1.type == Type::Int ? std::atoi(val_1_str.c_str()) : std::stod(val_1_str.c_str());
    auto val_2_num = val2.type == Type::Int ? std::atoi(val_2_str.c_str()) : std::stod(val_2_str.c_str());

    auto computed = val_1_num;

    if (operator_type == OperatorType::PLUS)
    {
        computed += val_2_num;
    }
    else if (operator_type == OperatorType::MINUS)
    {
        computed -= val_2_num;
    }
    else if (operator_type == OperatorType::MULT)
    {
        computed *= val_2_num;
    }
    else if (operator_type == OperatorType::DIV)
    {
        if ((val2.type == Type::Int && val_2_num == 0) ||
            (val2.type == Type::Dec && val_2_num == 0.0))
        {
            ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "Divide by 0 exception", -1, DIV_BY_0);
        }
        else
        {
            computed /= val_2_num;
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Invalid operator used in arithmetic expression", -1, INVALID_OPERATOR);
    }

    return computed;
}

Value Expression::or_compute(Value val1, ExprNode *expr2)
{
    Value val;
    val.type = Type::Bool;

    // Assume true (short circuit) unless otherwise
    val.token.lexeme = "true";
    val.token.type = TokenType::TRUE;

    if (val1.token.type == TokenType::FALSE)
    {
        Value val2 = get_expr_node_value(expr2);
        val.token.lexeme = val2.token.lexeme;
        val.token.type = val2.token.type;
    }

    return val;
}

Value Expression::and_compute(Value val1, ExprNode *expr2)
{
    Value val;
    val.type = Type::Bool;
    val.token.lexeme = "false";
    val.token.type = TokenType::FALSE;

    if (val1.token.type == TokenType::TRUE)
    {
        Value val2 = get_expr_node_value(expr2);
        val.token.lexeme = val2.token.lexeme;
        val.token.type = val2.token.type;
    }

    return val;
}

bool Expression::values_xor(Value val1, Value val2)
{
    assert(val1.type == Type::Bool && val2.type == Type::Bool);

    return (val1.token.type == TokenType::TRUE && val2.token.type == TokenType::FALSE) ||
           (val1.token.type == TokenType::FALSE && val2.token.type == TokenType::TRUE);
}

bool Expression::values_or(Value val1, Value val2)
{
    assert(val1.type == Type::Bool && val2.type == Type::Bool);

    return val1.token.type == TokenType::TRUE || val2.token.type == TokenType::TRUE;
}

bool Expression::values_and(Value val1, Value val2)
{
    assert(val1.type == Type::Bool && val2.type == Type::Bool);

    return val1.token.type == TokenType::TRUE && val2.token.type == TokenType::TRUE;
}

bool Expression::values_less_than(Value val1, Value val2)
{
    const char *val1_cstr = val1.token.lexeme.c_str();
    const char *val2_cstr = val2.token.lexeme.c_str();
    auto operand1 = val1.type == Type::Int ? std::atoi(val1_cstr) : std::stod(val1_cstr);
    auto operand2 = val2.type == Type::Int ? std::atoi(val2_cstr) : std::stod(val2_cstr);

    return operand1 < operand2;
}

bool Expression::values_greater_than(Value val1, Value val2)
{
    const char *val1_cstr = val1.token.lexeme.c_str();
    const char *val2_cstr = val2.token.lexeme.c_str();
    auto operand1 = val1.type == Type::Int ? std::atoi(val1_cstr) : std::stod(val1_cstr);
    auto operand2 = val2.type == Type::Int ? std::atoi(val2_cstr) : std::stod(val2_cstr);

    return operand1 > operand2;
}

// Helper function. Given two values, returns true if they are the equal, false otherwise
bool Expression::values_are_equal(Value val1, Value val2)
{
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
        int operand1 = std::atoi(val1.token.lexeme.c_str());
        int operand2 = std::atoi(val2.token.lexeme.c_str());

        is_equal = operand1 == operand2;
    }
    else if (val1.type == Type::Dec && val2.type == Type::Dec)
    {
        double operand1 = std::stod(val1.token.lexeme.c_str());
        double operand2 = std::stod(val2.token.lexeme.c_str());

        is_equal = operand1 == operand2;
    }

    return is_equal;
}

void Expression::assert_valid_type(Value val1, Value val2, OperatorType operator_type)
{
    bool is_valid = true;

    if (val1.type == Type::Void || val2.type == Type::Void || val1.type == Type::Invalid || val2.type == Type::Invalid)
    {
        std::cout << "assert_valid_type error. One of the operands has a void or invalid type during evaluation of the expression" << std::endl;
        assert(false);
        exit(EXIT_FAILURE);
    }

    if (operator_type == OperatorType::MINUS ||
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
        if (val1.type != Type::Bool || val2.type != Type::Bool)
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
    else if (operator_type == OperatorType::PLUS)
    {
        if (val1.type == Type::Bool && val2.type != Type::String ||
            val2.type == Type::Bool && val1.type != Type::String)
        {
            is_valid = false;
        }
    }

    if (is_valid == false)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Operator invalid for operands", -1, INVALID_OPERATION);
    }
}

Value Expression::compute(Value val1, Value val2, OperatorType operator_type)
{
    assert_valid_type(val1, val2, operator_type);

    Value result;

    if (operator_type == OperatorType::PLUS || operator_type == OperatorType::MINUS || operator_type == OperatorType::MULT || operator_type == OperatorType::DIV)
    {
        if ((val1.type == Type::String || val2.type == Type::String) && operator_type == OperatorType::PLUS)
        {
            std::string res_str = val1.token.lexeme + val2.token.lexeme;
            result.type = Type::String;
            result.token.type = TokenType::STRING;
            result.token.lexeme = res_str;
        }
        else
        {
            auto computed = arith_compute(val1, val2, operator_type);

            if (val1.type == Type::Int && val2.type == Type::Int)
            {
                result.type = Type::Int;
                result.token.type = TokenType::INT_NUM;
                int computed_int = computed;
                result.token.lexeme = std::to_string(computed_int);
            }
            else
            {
                result.type = Type::Dec;
                result.token.type = TokenType::DEC_NUM;
                result.token.lexeme = std::to_string(computed);
            }
        }
    }
    else if (operator_type == OperatorType::LT || operator_type == OperatorType::GT || operator_type == OperatorType::LEQ || operator_type == OperatorType::GEQ)
    {
        result.type = Type::Bool;

        if ((operator_type == OperatorType::LT && values_less_than(val1, val2)) ||
            (operator_type == OperatorType::GT && values_greater_than(val1, val2)) ||
            (operator_type == OperatorType::LEQ && values_greater_than(val1, val2) == false) ||
            (operator_type == OperatorType::GEQ && values_less_than(val1, val2) == false))
        {
            result.token.type = TokenType::TRUE;
            result.token.lexeme = "true";
        }
        else
        {
            result.token.type = TokenType::FALSE;
            result.token.lexeme = "false";
        }
    }
    else if (operator_type == OperatorType::XOR)
    {
        result.type = Type::Bool;

        if (values_xor(val1, val2))
        {
            result.token.type = TokenType::TRUE;
            result.token.lexeme = "true";
        }
        else
        {
            result.token.type = TokenType::FALSE;
            result.token.lexeme = "false";
        }
    }
    else if (operator_type == OperatorType::IS || operator_type == OperatorType::NEQ)
    {
        result.type = Type::Bool;
        bool is_equal = values_are_equal(val1, val2);

        if ((is_equal == true && operator_type == OperatorType::IS) || (is_equal == false && operator_type == OperatorType::NEQ))
        {
            result.token.type = TokenType::TRUE;
            result.token.lexeme = "true";
        }
        else
        {
            result.token.type = TokenType::FALSE;
            result.token.lexeme = "false";
        }
    }
    else // debugging
    {
        std::cout << "Invalid operator type in compute in expression.cpp" << std::endl;
        assert(false);
        exit(EXIT_FAILURE);
    }

    return result;
}

/* END OF COMPUTE FUNCTIONS */

/* BEGINNING OF RPN FUNCTIONS */

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
    assert(exprNode->expr_type == ExprType::PAREN);

    ParenNode *paren = (ParenNode *)exprNode;

    return paren->is_left == true;
}

std::deque<ExprNode *> Expression::infix_to_rev_polish()
{
    std::deque<ExprNode *> output_queue;
    std::stack<ExprNode *> op_stk;

    for (auto term : term_list)
    {
        if (term->expr_type == ExprType::LOAD || term->expr_type == ExprType::FUNC_CALL)
        {
            output_queue.push_back(term);
        }
        else if (term->expr_type == ExprType::PAREN && is_left_paren(term) == true)
        {
            op_stk.push(term);
        }
        else if (term->expr_type == ExprType::OPERATOR)
        {
            ExprNode *op1 = term;
            while (op_stk.empty() == false &&
                   ((op_stk.top())->expr_type != ExprType::PAREN ||
                    is_left_paren(op_stk.top()) == false) &&
                   compare_precedence(op1, op_stk.top()))
            {
                ExprNode *pop = op_stk.top();
                op_stk.pop();
                output_queue.push_back(pop);
            }

            op_stk.push(op1);
        }
        else if (term->expr_type == ExprType::PAREN && is_left_paren(term) == false)
        {
            while (op_stk.empty() == false && (op_stk.top()->expr_type != ExprType::PAREN || is_left_paren(op_stk.top()) == false))
            {
                ExprNode *pop = op_stk.top();
                op_stk.pop();
                output_queue.push_back(pop);
            }

            assert(op_stk.empty() == false && (op_stk.top()->expr_type == ExprType::PAREN && is_left_paren(op_stk.top()) == true));

            ExprNode *lparen = op_stk.top();
            op_stk.pop();
        }
    }

    while (op_stk.empty() == false)
    {
        assert(op_stk.top()->expr_type != ExprType::PAREN || is_left_paren(op_stk.top()) == false);
        output_queue.push_back(op_stk.top());
        op_stk.pop();
    }

    return output_queue;
}

/* END OF RPN FUNCTIONS */

Value Expression::get_expr_node_value(ExprNode *expr_node)
{
    Value val;

    if (expr_node->expr_type == ExprType::FUNC_CALL)
    {
        FuncCallNode *func_call = (FuncCallNode *)expr_node;
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
    else if (expr_node->expr_type == ExprType::LOAD)
    {
        LoadNode *load = (LoadNode *)expr_node;
        load->evaluate();
        val = load->value;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Evaluation encountered invalid expression operand", -1, INVALID_OPERAND);
    }

    return val;
}

void Expression::evaluate()
{
    if (term_list.empty())
    {
        return;
    }

    std::deque<ExprNode *> output_queue = infix_to_rev_polish();
    std::stack<ExprNode *> operand_stack;

    if (output_queue.empty()) // debugging purposes
    {
        std::cout << "Output queue should not be empty (BUG in expression.cpp)" << std::endl;
    }

    // Special case? Only 1 term in the expression
    if (output_queue.size() == 1)
    {
        ExprNode *expr = output_queue.back();
        if (expr->expr_type == ExprType::FUNC_CALL)
        {
            FuncCallNode *func_call = (FuncCallNode *)expr;
            func_call->evaluate();
            value = func_call->value;
        }
        else
        {
            LoadNode *load_node = (LoadNode *)expr;
            load_node->evaluate();
            value = load_node->value;
        }
        return;
    }

    for (auto expr_node : output_queue)
    {
        if (expr_node->expr_type == ExprType::OPERATOR)
        {
            // Extract the expression nodes
            ExprNode *exprNode1 = operand_stack.top();
            operand_stack.pop();

            ExprNode *exprNode2 = operand_stack.top();
            operand_stack.pop();

            OperatorNode *operator_node = (OperatorNode *)expr_node;

            OperatorType operator_type = ((OperatorNode *)operator_node)->operator_type;

            Assoc assoc = op_to_assoc[operator_type];

            // by default, compute uses right associativity
            if (assoc == Assoc::LEFT)
            {
                std::swap(exprNode1, exprNode2);
            }

            Value curr_result;
            Value val1 = get_expr_node_value(exprNode1);

            if (operator_type == OperatorType::OR)
            {
                Value or_result = or_compute(val1, exprNode2);
                curr_result = or_result;
            }
            else if (operator_type == OperatorType::AND)
            {
                Value and_result = and_compute(val1, exprNode2);
                curr_result = and_result;
            }
            else
            {
                Value val2 = get_expr_node_value(exprNode2);
                curr_result = compute(val1, val2, operator_type);
            }

            // Wrap value into a constant loadnode
            LoadNode *load_const = new LoadNode(ExprType::LOAD, curr_result, -1, true);

            operand_stack.push(load_const);
        }
        else if (expr_node->expr_type == ExprType::FUNC_CALL || expr_node->expr_type == ExprType::LOAD)
        {
            operand_stack.push(expr_node);
        }
        else
        {
            std::cout << "Internal error. Parenthesis in the output_queue in expression.cpp" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    assert(operand_stack.size() == 1);

    LoadNode *final_result = (LoadNode *)operand_stack.top();

    value = final_result->value;
}